#pragma once

#include "Piece.h"

class Pawn: public Piece
{
public:
	Pawn(EPieceColor color);
	bool CanMove();
};


