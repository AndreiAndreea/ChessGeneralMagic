#pragma once

#include "Piece.h"

class King: public Piece
{
public:
	King(EPieceColor color);
	bool CanMove();
};

