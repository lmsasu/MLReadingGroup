#pragma once
#include <cstdint>
#include <array>
#include <optional>
#include <tuple>

class Board
{
public:
	enum class Piece
	{
		Cross,
		Nought
	};

	enum class State
	{
		None,
		Win,
		Draw
	};

	using Position = std::tuple<uint8_t, uint8_t>;

public:
	static const uint8_t kRows = 3;
	static const uint8_t kColumns = 3;

public:
	State Check() const;
	void Reset();

	std::array<std::array<std::optional<Piece>, kColumns>, kRows>::const_iterator begin() const;
	std::array<std::array<std::optional<Piece>, kColumns>, kRows>::const_iterator end() const;
	std::optional<Piece>& operator [] (const Position& position);
	const std::optional<Piece>& operator [] (const Position& position) const;

private:
	std::array<std::array<std::optional<Piece>, kColumns>, kRows> m_pieces;
};

