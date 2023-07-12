#include "Rook.h"
#include "Board.h"

Rook::Rook(EPieceColor color)
	: Piece(EPieceType::Rook, color)
{

}

bool Rook::CanMove(Position startPos, Position endPos, const Board& board)
{
	if (startPos.first != endPos.first && startPos.second != endPos.second || (startPos.first == endPos.first && startPos.second == endPos.second))
		return false;

	BoardType localBoard = board.GetBoard();

	int maxi = startPos.first > endPos.first ? startPos.first : endPos.first;
	int mini = startPos.first > endPos.first ? startPos.first : endPos.first;

	// vertical movement
	if (startPos.first < endPos.first)
	{
		for (int i = startPos.first + 1; i < endPos.first; i++)
			if (localBoard[i][startPos.second] != nullptr)
				return false;
	}
	else
		for (int i = startPos.first - 1; i > endPos.first; i--)
		{
			if (localBoard[i][startPos.second] != nullptr)
				return false;
		}

	//horizontal movement
	if (startPos.second < endPos.second)
	{
		for (int i = startPos.second + 1; i < endPos.second; i++)
			if (localBoard[startPos.first][i] != nullptr)
				return false;
	}
	else
		for (int i = startPos.second - 1; i > endPos.second; i--)
		{
			if (localBoard[startPos.first][i] != nullptr)
				return false;
		}

	return true;
}