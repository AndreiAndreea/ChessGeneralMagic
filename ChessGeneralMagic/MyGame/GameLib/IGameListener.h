#pragma once

#include "EGameResult.h"

class IGameListener
{
public:
	virtual void OnMoveMade() = 0;
	virtual void OnPawnUpgrade() = 0;
	virtual void OnGameOver(EGameResult result) = 0;

	virtual ~IGameListener() = default;
};