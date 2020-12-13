#include "ConsoleRenderer.h"
#include <iostream>

ConsoleRenderer::ConsoleRenderer(bool isActive) : m_isActive(isActive)
{
	// empty
}

void ConsoleRenderer::SetActive(bool active)
{
	m_isActive = active;
}

void ConsoleRenderer::Draw(const Board& board) const
{
	if (!m_isActive)
		return;

	for (const auto& line : board)
	{
		for (const auto& pieceOptional : line)
		{
			if (pieceOptional)
			{
				switch (pieceOptional.value())
				{
				case Board::Piece::Cross: 
					std::cout << "X";
					break;
				case Board::Piece::Nought:
					std::cout << "0";
					break;
				}
			}
			else
			{
				std::cout << "_";
			}

			std::cout << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void ConsoleRenderer::ShowEndScreen(const IPlayer* player) const
{
	if (!m_isActive)
		return;

	std::cout << "Congratulations " << player->GetName() << ". You won! :)\n";
}

void ConsoleRenderer::ShowEndScreen() const
{
	if (!m_isActive)
		return;

	std::cout << "We have a tie! :(\n";
}
