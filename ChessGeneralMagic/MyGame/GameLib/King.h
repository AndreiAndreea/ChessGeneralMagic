#pragma once

#include "Piece.h"

class King: public Piece
{
public:
	King();
	King(bool white);
	bool CanMove();
};

