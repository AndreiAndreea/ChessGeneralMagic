#pragma once

#include "Piece.h"

class Pawn: public Piece
{
public:
	Pawn(EPieceColor color);
	bool CanMove(Position startPos, Position endPos, const Board& board);
};


