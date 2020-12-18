#include "TicTacToeGame.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "ConsoleRenderer.h"
#include "AiPlayer.h"

#include <memory>

void TicTacToeGame::Run()
{
	Board board;
	std::unique_ptr<IPlayer> firstPlayer = std::make_unique<AiPlayer>(board, "DoctorCross");
	std::unique_ptr<IPlayer> secondPlayer = std::make_unique<AiPlayer>(board, "DoctorNought");

	ConsoleRenderer renderer(false);

	const uint32_t numberOfPlays = 1000;

	for (uint32_t currentPlay = 0; currentPlay < numberOfPlays; ++currentPlay)
	{
		// on last iteration, play againt the ai as human
		if (currentPlay == numberOfPlays - 1)
		{
			renderer.SetActive(true);
			secondPlayer = std::make_unique<HumanPlayer>("HumanPlayer");
		}

		board.Reset();
		Board::Piece currentPiece = Board::Piece::Cross;
		Board::Piece nextPiece = Board::Piece::Nought;
		IPlayer* currentPlayer = firstPlayer.get();
		IPlayer* nextPlayer = secondPlayer.get();

		bool isGameActive = true;
		while (isGameActive)
		{
			renderer.Draw(board);

			bool isInputOk = false;
			while (!isInputOk)
			{
				const Board::Position& position = currentPlayer->GetNextAction();
				if (!board[position])
				{
					board[position] = currentPiece;
					isInputOk = true;
				}
			}

			auto state = board.Check();
			switch (state)
			{
			case Board::State::Win:
			{
				renderer.Draw(board);
				renderer.ShowEndScreen(currentPlayer);
				auto player1 = dynamic_cast<AiPlayer*>(currentPlayer);
				if (player1)
					player1->FeedReward(1.f);
				auto player2 = dynamic_cast<AiPlayer*>(nextPlayer);
				if (player2)
					player2->FeedReward(0.f);
				isGameActive = false;
				break;
			}
			case Board::State::Draw:
			{
				renderer.Draw(board);
				renderer.ShowEndScreen();
				auto player1 = dynamic_cast<AiPlayer*>(currentPlayer);
				if (player1)
					player1->FeedReward(0.5f);
				auto player2 = dynamic_cast<AiPlayer*>(nextPlayer);
				if (player2)
					player2->FeedReward(0.5f);
				isGameActive = false;
				break;
			}
			case Board::State::None:
				std::swap(currentPlayer, nextPlayer);
				std::swap(currentPiece, nextPiece);
			}
		}
	}
}
