#pragma once

#include "Piece.h"

class Queen: public Piece
{
public:
	Queen(EPieceColor color);
	bool CanMove();
};

