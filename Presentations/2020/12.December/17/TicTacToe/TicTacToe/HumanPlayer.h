#pragma once
#include "IPlayer.h"

class HumanPlayer : public IPlayer
{
public:
	HumanPlayer(const std::string& name);

	Board::Position GetNextAction() override;

	const std::string& GetName() const override;

private:
	std::string m_name;
};

