#pragma once
#include "Board.h"
#include "HumanPlayer.h"

class ConsoleRenderer
{
public:
	ConsoleRenderer(bool isActive = true);

	void SetActive(bool active);

	void Draw(const Board& board) const;
	// Shows a winning message
	void ShowEndScreen(const IPlayer* player) const;
	// Shows a tie message
	void ShowEndScreen() const;

private:
	bool m_isActive;
};

