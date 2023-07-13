#include "King.h"
#include "Board.h"


King::King(EPieceColor color) 
    : Piece(EPieceType::King, color)
{

}

bool King::CanMove(Position startPos, Position endPos, const Board& board)
{
	EPieceColor currentColor = GetColor();
	BoardType localBoard = board.GetBoard();
	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

	if (startPos.first == endPos.first && startPos.second == endPos.second)
		return false;

	if (std::abs(startPos.first - endPos.first) > 1 && std::abs(startPos.second - endPos.second) > 1)
		return false;

    return true;
}
