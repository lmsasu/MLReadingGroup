#pragma once
#include "IPlayer.h"
#include <unordered_map>
#include <vector>

class AiPlayer : public IPlayer
{
public:
	AiPlayer(Board& board, const std::string& policyName);
	~AiPlayer() override;

	// Inherited via IPlayer
	virtual Board::Position GetNextAction() override;
	virtual const std::string& GetName() const override;

	void FeedReward(float target);

private:
	static std::vector<Board::Position> GenerateActionCollection(const Board& board);
	void SavePolicy() const;
	void LoadPolicy();

private:
	Board& m_board;
	std::unordered_map<int64_t, float> m_stateActionCosts;
	std::vector<int64_t> m_previousStateActions;
	std::string m_policyName;
};