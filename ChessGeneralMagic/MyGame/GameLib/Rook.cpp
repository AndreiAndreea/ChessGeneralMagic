#include "Rook.h"
#include "Board.h"

Rook::Rook(EPieceColor color)
	: Piece(EPieceType::Rook, color)
{

}

bool Rook::CanMove(Position startPos, Position endPos, const Board& board)
{
	/*PositionList possibleMoves;
	possibleMoves = GetPossibleMoves(startPos, board);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
		return true;

	return false;*/

	EPieceColor currentColor = GetColor();
	PieceMatrix localBoard = board.GetBoard();

	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

	if (startPos.first != endPos.first && startPos.second != endPos.second || (startPos.first == endPos.first && startPos.second == endPos.second))
		return false;

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
		{
			if (localBoard[startPos.first][i] != nullptr)
				return false;
		}
	}
	else
		for (int i = startPos.second - 1; i > endPos.second; i--)
		{
			if (localBoard[startPos.first][i] != nullptr)
				return false;
		}

	return true;
}

PositionList Rook::GetPossibleMoves(Position piecePos, const Board& board)
{
	PositionList possibleMoves;
	EPieceColor pieceColor = GetColor();
	auto localBoard = board.GetBoard();

	//vertical down
	int i = piecePos.first + 1;
	while (i <= 8)
	{
		if (localBoard[i][piecePos.second] != nullptr)
		{
			if (localBoard[i][piecePos.second]->GetColor() != pieceColor)
				possibleMoves.push_back(Position(i, piecePos.second));
			break;
		}
		else
			possibleMoves.push_back(Position(i, piecePos.second));
		i++;
	}

	//horizontal left
	i = piecePos.second - 1;
	while (i >= 1)
	{
		if (localBoard[piecePos.first][i] != nullptr)
		{
			if (localBoard[piecePos.first][i]->GetColor() != pieceColor)
				possibleMoves.push_back(Position(piecePos.first, i));
			break;
		}
		else
			possibleMoves.push_back(Position(piecePos.first, i));
		i--;
	}

	//vertical up
	i = piecePos.first - 1;
	while (i >= 1)
	{

		if (localBoard[i][piecePos.second] != nullptr)
		{
			if (localBoard[i][piecePos.second]->GetColor() != pieceColor)
				possibleMoves.push_back(Position(i, piecePos.second));
			break;
		}
		else
			possibleMoves.push_back(Position(i, piecePos.second));
		i--;
	}

	//horizontal right
	i = piecePos.second + 1;
	while (i <= 8)
	{
		if (localBoard[piecePos.first][i] != nullptr)
		{
			if (localBoard[piecePos.first][i]->GetColor() != pieceColor)
				possibleMoves.push_back(Position(piecePos.first, i));
			break;
		}
		else
			possibleMoves.push_back(Position(piecePos.first, i));
		i++;
	}
	return possibleMoves;
}