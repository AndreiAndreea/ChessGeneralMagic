#pragma once

#include "Piece.h"

class Knight: public Piece
{
public:
	Knight(EPieceColor color);
	bool CanMove();
};

