#pragma once

#include "Piece.h"

class Knight: public Piece
{
public:
	Knight();
	Knight(bool white);
	bool CanMove();
};

