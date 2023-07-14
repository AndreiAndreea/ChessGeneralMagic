#pragma once

#include <memory>

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
	virtual EPlayer GetWinner() const = 0;
	virtual bool IsGameOver() const = 0;
	//virtual void MakeMove(Position startPos, Position endPos, Board& board)=0;


	virtual ~IGame() = default;
};

