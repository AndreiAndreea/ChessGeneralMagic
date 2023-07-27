#pragma once

#include "EGameResult.h"
#include "PositionList.h"

class IGameListener
{
public:
	virtual void OnMoveMade(Position startPos, Position endPos, PositionList prevPossibleMoves) = 0;
	virtual void OnPawnUpgrade() = 0;
	virtual void OnGameOver(EGameResult result) = 0;

	virtual ~IGameListener() = default;
};