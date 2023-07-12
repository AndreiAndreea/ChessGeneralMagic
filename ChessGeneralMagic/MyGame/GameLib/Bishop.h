#pragma once

#include "Piece.h"

class Bishop: public Piece
{
public:
	Bishop(EPieceColor color);
	bool CanMove(Position startPos, Position endPos, const Board& board);
};

