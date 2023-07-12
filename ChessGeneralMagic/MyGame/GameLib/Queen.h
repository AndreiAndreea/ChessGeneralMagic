#pragma once

#include "Piece.h"

class Queen: public Piece
{
public:
	Queen();
	Queen(bool white);
	bool CanMove();
};

