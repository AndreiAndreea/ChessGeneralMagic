#pragma once

#include "Piece.h"

class Bishop: public Piece
{
public:
	Bishop();
	Bishop(bool white);
	bool CanMove();
};

