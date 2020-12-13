#include "HumanPlayer.h"

#include <iostream>

HumanPlayer::HumanPlayer(const std::string& name) : m_name(name)
{
	// empty
}

Board::Position HumanPlayer::GetNextAction()
{
	std::cout << m_name << ", where do you want to put your chessman?\n";
	
	std::cout << "row and colum: ";
	int row;
	std::cin >> row;
	int column;
	std::cin >> column;
	
	return {row, column};
}

const std::string& HumanPlayer::GetName() const
{
	return m_name;
}
