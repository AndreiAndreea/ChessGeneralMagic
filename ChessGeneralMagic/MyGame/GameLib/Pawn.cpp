#include "Pawn.h"

Pawn::Pawn(bool white) : Piece(white) { type = "P"; }


bool Pawn::CanMove()
{
	////checking the direction of the movement
	//if (white)
	//{
	//	if (start.x - end.x >= 0)
	//		return false;
	//}
	//else
	//{
	//	if (start.x - end.x <= 0)
	//		return false;
	//}

	////checking capturing possibility
	//if (start.y )

    return false;
}
