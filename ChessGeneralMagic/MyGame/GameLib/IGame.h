#pragma once

#include "EPieceColor.h"
#include "EPieceType.h"

#include <memory>

enum class EPlayer
{
	White,
	Black,
	None
};

using IGamePtr = std::shared_ptr<class IGame>;

class IPieceInfo
{
public:
	virtual EPieceColor GetColor() = 0;
	virtual EPieceType GetType() = 0;

	virtual ~IPieceInfo() = default;
};

using IPieceInfoPtr = std::shared_ptr<IPieceInfo>;
using Position = std::pair<int, int>;


class IGame
{

public:
	static IGamePtr Produce();

	virtual void Play() = 0;
	virtual EPlayer GetWinner() const = 0;
	virtual bool IsGameOver() const = 0;
	virtual void MakeMove(Position startPos, Position endPos)=0;

	virtual IPieceInfoPtr GetPieceInfo(int i, int j) = 0;

	virtual ~IGame() = default;
};

