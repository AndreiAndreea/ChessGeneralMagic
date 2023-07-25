#pragma once

class IGameListener
{
public:
	virtual void OnMoveMade() const = 0;
	virtual void OnPawnUpgrade()const = 0;
	virtual void OnGameOver() const = 0;
};