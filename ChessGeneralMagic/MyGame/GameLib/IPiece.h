#pragma once

#include "EPieceColor.h"
#include "EPieceType.h"

#include <utility>
#include<vector>

class Board;

using Position = std::pair<int, int>;
using PositionList = std::vector<Position>;

class IPiece
{
public:
	virtual EPieceColor GetColor() const = 0;
	virtual EPieceType GetType() const = 0;
	virtual bool CanMove(Position startPos, Position endPos, const Board& board) = 0;
	virtual void SetPossibleMoves(Position picePos, PositionList& possibleMoves, const Board& board)=0;

	virtual ~IPiece() = default;
};