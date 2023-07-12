#pragma once

#include "Piece.h"
#include "Board.h"

class Rook: public Piece
{
public:
	Rook(EPieceColor color);
	bool CanMove(Position stratPos, Position endPos, Board board);
};

