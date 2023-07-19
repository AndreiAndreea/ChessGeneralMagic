#pragma once

#include "EPieceColor.h"
#include "EPieceType.h"

#include <vector>
#include <memory>
#include <string>
#include<utility>

enum class EPlayer
{
	White,
	Black,
	None
};

class IPieceInfo
{
public:
	virtual EPieceColor GetColor() const = 0;
	virtual EPieceType GetType() const = 0;

	virtual ~IPieceInfo() = default;
};

using Position = std::pair<int, int>;
using IPieceInfoPtr = std::shared_ptr<IPieceInfo>;
using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual void Play() = 0;
	virtual EPlayer GetWinner() const = 0;
	virtual EPlayer GetCurrentPlayer() const = 0;
	virtual bool IsGameOver() const = 0;
	virtual bool MakeMove(std::string startPosStr, std::string endPosStr) = 0;

	virtual IPieceInfoPtr GetPieceInfo(int i, int j) const = 0;

	virtual ~IGame() = default;
};