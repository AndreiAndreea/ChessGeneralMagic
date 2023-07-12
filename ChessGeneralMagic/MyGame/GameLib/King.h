#pragma once

#include "Piece.h"

class King: public Piece
{
public:
	King(EPieceColor color);
	bool CanMove(Position startPos, Position endPos, const Board& board);
};

