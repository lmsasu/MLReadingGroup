#pragma once
#include "Board.h"

#include <string>

struct IPlayer
{
	virtual ~IPlayer() = default;

	virtual Board::Position GetNextAction() = 0;
	virtual const std::string& GetName() const = 0;
};