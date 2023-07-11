#pragma once
#include "Piece.h"

struct Position
{
	int x, y;

	Position(int a = 0, int b = 0)
	{
		x = a;
		y = b;
	}
};

class Spot
{
private:
	Piece* piece = nullptr;
	Position pos;
public:
	Spot();
	void setPosition();
	void setTypePiece();
	Position getPosition();
	Piece getPiece();
};

