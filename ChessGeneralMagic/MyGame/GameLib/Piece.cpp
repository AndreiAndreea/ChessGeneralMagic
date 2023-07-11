#include "Piece.h"

Piece::Piece(bool white)
{
	this->setColor(white);
}

bool Piece::isWhite()
{
	return this->white;
}

void Piece::setColor(bool white)
{
	this->white = white;
}
