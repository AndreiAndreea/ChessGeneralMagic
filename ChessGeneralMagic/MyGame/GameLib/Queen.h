#pragma once

#include "Piece.h"

class Board;

class Queen: public Piece
{
public:
	Queen(EPieceColor color);
	bool CanMove(Position startPos, Position endPos, const Board& board);
};

