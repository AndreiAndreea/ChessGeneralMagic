#include "Pawn.h"
#include "Board.h"


Pawn::Pawn(EPieceColor color)
	: Piece(EPieceType::Pawn, color)
{

}

bool Pawn::CanMove(Position startPos, Position endPos, const Board& board)
{

	EPieceColor currentColor = GetColor();
	BoardType localBoard = board.GetBoard();
	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

	//checking the direction of the movement
	if (currentColor == EPieceColor::White)
	{
		if (startPos.first >= endPos.first)
			return false;
	}
	else
	{
		if (startPos.first <= endPos.first)
			return false;
	}

	if (std::abs(startPos.first - endPos.first) == 2 && (startPos.first != 7 && startPos.first != 2))
		return false;

	if (std::abs(startPos.first - endPos.first) > 2)
		return false;

	//diagonally
	if (endPos.second != startPos.second)
		if (std::abs(endPos.second != startPos.second) > 1)
			return false;
		else
			if (localBoard[endPos.first][endPos.second] == nullptr)

				return false;

	if (std::abs(startPos.first - endPos.first) > 2)
		return false;

    return true;
}
