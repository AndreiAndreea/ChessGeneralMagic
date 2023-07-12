#pragma once

#include "Piece.h"

class Pawn: public Piece
{
public:
	Pawn();
	Pawn(bool white);
	bool CanMove();
};


