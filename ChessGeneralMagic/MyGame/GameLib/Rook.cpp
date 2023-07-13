#include "Rook.h"
#include "Board.h"

Rook::Rook(EPieceColor color)
	: Piece(EPieceType::Rook, color)
{

}

bool Rook::CanMove(Position startPos, Position endPos, const Board& board)
{
	EPieceColor currentColor = GetColor();

	if (startPos.first != endPos.first && startPos.second != endPos.second || (startPos.first == endPos.first && startPos.second == endPos.second))
		return false;

	BoardType localBoard = board.GetBoard();

	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

	// vertical movement
	if (startPos.first < endPos.first)
	{
		for (int i = startPos.first + 1; i <= endPos.first; i++)
			if (localBoard[i][startPos.second] != nullptr)
				return false;
	}
	else
		for (int i = startPos.first - 1; i >= endPos.first; i--)
		{
			if (localBoard[i][startPos.second] != nullptr)
				return false;
		}

	//horizontal movement
	if (startPos.second < endPos.second)
	{
		for (int i = startPos.second + 1; i <= endPos.second; i++)
		{
			if (localBoard[startPos.first][i] != nullptr)
				return false;
		}
	}
	else
		for (int i = startPos.second - 1; i >= endPos.second; i--)
		{
			if (localBoard[startPos.first][i] != nullptr)
				return false;
		}

	return true;
}