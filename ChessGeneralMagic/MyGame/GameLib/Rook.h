#pragma once

#include "Piece.h"

class Rook: public Piece
{
public:
	Rook();
	Rook(bool white);
	bool CanMove();
};

