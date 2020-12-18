#include "AiPlayer.h"
#include <limits>
#include <random>
#include <fstream>

std::random_device randomDevice;
std::mt19937 randomEngine(randomDevice());

const float initialEstimation = 0.5f;
const float explorationRate = 0.1f;
const float learningRate = 0.1f;

AiPlayer::AiPlayer(Board& board, const std::string& policyName) : m_board(board), m_policyName(policyName)
{
	LoadPolicy();
}

AiPlayer::~AiPlayer()
{
	SavePolicy();
}

Board::Position AiPlayer::GetNextAction()
{
	std::vector<Board::Position> possibleActions = GenerateActionCollection(m_board);
	std::reference_wrapper<Board::Position> bestAction = possibleActions[0];
	int64_t bestStateActionHash = 0;
	
	std::bernoulli_distribution bernDist(explorationRate);	// generates 'true' with explorationRate probability
	if (bernDist(randomEngine))
	{
		// randomly pick an action
		std::uniform_int_distribution<uint32_t> uniformDist(0, (uint32_t)possibleActions.size() - 1);
		bestAction = possibleActions[uniformDist(randomEngine)];
		bestStateActionHash = m_board.GetHashWithPosition(bestAction);
		auto itMap = m_stateActionCosts.insert(std::make_pair(bestStateActionHash, initialEstimation));
	}
	else
	{
		// compute best action
		float bestActionEstimation = -std::numeric_limits<float>::infinity();
		for (auto& action : possibleActions)
		{
			int64_t stateActionHash = m_board.GetHashWithPosition(action);
			auto itMap = m_stateActionCosts.insert(std::make_pair(stateActionHash, initialEstimation));
			float currentActionEstimation = itMap.first->second;
			if (currentActionEstimation > bestActionEstimation)
			{
				bestAction = action;
				bestStateActionHash = stateActionHash;
				bestActionEstimation = currentActionEstimation;
			}
		}
	}

	m_previousStateActions.emplace_back(bestStateActionHash);

	return bestAction;
}

const std::string& AiPlayer::GetName() const
{
	return m_policyName;
}

void AiPlayer::FeedReward(float target)
{
	for (auto it = m_previousStateActions.rbegin(); it != m_previousStateActions.rend(); ++it)
	{
		const auto& stateAction = *it;
		float& estimation = m_stateActionCosts[stateAction];
		estimation = estimation + learningRate * (target - estimation);
		target = estimation;
	}

	m_previousStateActions.clear();
}

std::vector<Board::Position> AiPlayer::GenerateActionCollection(const Board& board)
{
	std::vector<Board::Position> possibleActions;

	for (uint32_t i = 0; i < Board::kRows; ++i)
	{
		for (uint32_t j = 0; j < Board::kColumns; ++j)
		{
			Board::Position position = { i, j };
			if (!board[position])
			{
				possibleActions.emplace_back(position);
			}
		}
	}

	return possibleActions;
}

void AiPlayer::SavePolicy() const
{
	std::ofstream out(m_policyName);

	for (const auto& pair : m_stateActionCosts)
		if (pair.second != initialEstimation)	// skip not modified values
			out << pair.first << ' ' << pair.second << std::endl;
}

void AiPlayer::LoadPolicy()
{
	std::ifstream in(m_policyName);
	if (in.fail())
		return;

	while (!in.eof())
	{
		int64_t stateActionHash;
		float estimation;
		in >> stateActionHash >> estimation;
		m_stateActionCosts[stateActionHash] = estimation;
	}
}
