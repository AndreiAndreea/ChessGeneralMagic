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
		if (startPos.first - endPos.first >= 0)
			return false;
	}
	else
	{
		if (start.x - end.x <= 0)
			return false;
	}

	////checking capturing possibility
	//if (start.y )

    return false;
}
