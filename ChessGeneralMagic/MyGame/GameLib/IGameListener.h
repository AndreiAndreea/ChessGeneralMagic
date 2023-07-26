#pragma once

class IGameListener
{
public:
	virtual void OnMoveMade() = 0;
	virtual void OnPawnUpgrade() = 0;
	virtual void OnGameOver() = 0;
};