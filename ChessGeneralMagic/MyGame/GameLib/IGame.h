#pragma once

enum class EPlayer
{
	White,
	Black,
	None
};

using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{

public:
	static IGamePtr Produce();

	virtual void Play() = 0;
	virtual EPlayer getWinner() = 0;
	virtual bool isGameOver() = 0;

	virtual ~IGame() = default;
};

