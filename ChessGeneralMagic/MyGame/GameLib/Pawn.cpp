#include "Pawn.h"
#include "Board.h"


Pawn::Pawn(EPieceColor color)
	: Piece(EPieceType::Pawn, color)
{

}

bool Pawn::CanMove(Position startPos, Position endPos, const Board& board)
{
	EPieceColor color = GetColor();

	//checking the direction of the movement
	if (color == EPieceColor::White)
	{
		if (startPos.first >= endPos.first)
			return false;
	}
	else
	{
		if (startPos.first <= endPos.first)
			return false;
	}


	//checking capturing possibility
	//if (startPos.second ! )

    return true;
}
