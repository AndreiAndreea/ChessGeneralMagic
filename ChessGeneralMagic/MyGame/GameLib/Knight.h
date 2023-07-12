#pragma once

#include "Piece.h"

class Knight: public Piece
{
public:
	Knight();
	Knight(EPieceColor color);
	bool CanMove();
};

