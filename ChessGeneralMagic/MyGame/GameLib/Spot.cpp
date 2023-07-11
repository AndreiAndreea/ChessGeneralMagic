#include "Spot.h"

Spot::Spot()
{

}

void Spot::setPosition(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

Position Spot::getPosition()
{
	return pos;
}

Piece* Spot::getPiece()
{
	return piece;
}

void Spot::setPiece(Piece* p)
{
	piece = p;
}
