#include "Board.h"

#include <stdexcept>

Board::State Board::Check() const
{
	const uint8_t kResults = 8;		// 3 rows + 3 column + 1 main diagonal + 1 secondary diagonal
	std::array<int8_t, kResults> results {};
	int chessmanCount = 0;

	// traverse the board only once, but compute all results
	for (uint32_t i = 0; i < kRows; ++i)
	{
		for (uint32_t j = 0; j < kColumns; ++j)
		{
			if(m_pieces[i][j].has_value())
			{
				int8_t value;
				switch (m_pieces[i][j].value())
				{
				case Piece::Cross:
					value = 1;
					break;
				case Piece::Nought:
					value = -1;
					break;
				default:
					value = 0;
				}

				// rows
				results[i] += value;
				// columns
				results[3 + j] += value;
				// primary diagonal
				if (i == j)
					results[6] += value;
				// secondary diagonal
				if (i == kColumns - 1 - j)
					results[7] += value;

				++chessmanCount;
			}
		}
	}

	// check if we have winner
	for (auto result : results)
	{
		if (result == 3 || result == -3)
		{
			return State::Win;
		}
	}

	// check if it's a tie
	if (chessmanCount == kRows * kColumns)
	{
		return State::Draw;
	}

	return State::None;
}

void Board::Reset()
{
	memset(&m_pieces, 0, sizeof(m_pieces));
}

std::array<std::array<std::optional<Board::Piece>, Board::kColumns>, Board::kRows>::const_iterator Board::begin() const
{
	return m_pieces.begin();
}

std::array<std::array<std::optional<Board::Piece>, Board::kColumns>, Board::kRows>::const_iterator Board::end() const
{
	return m_pieces.end();
}

std::optional<Board::Piece>& Board::operator[](const Board::Position& position)
{
	auto& [line, column] = position;

	if (line < 0 || line > kRows || column < 0 || column > kColumns)
		throw std::out_of_range("Position out of bounds");

	return m_pieces[line][column];
}

const std::optional<Board::Piece>& Board::operator[](const Position& position) const
{
	auto& [line, column] = position;

	if (line < 0 || line > kRows || column < 0 || column > kColumns)
		throw std::out_of_range("Position out of bounds");

	return m_pieces[line][column];
}
