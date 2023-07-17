#include "Queen.h"
#include "Board.h"

Queen::Queen(EPieceColor color) 
    : Piece(EPieceType::Queen,color)
{

}

bool Queen::CanMove(Position startPos, Position endPos, const Board& board)
{
	Bishop bishop(EPieceColor::Black);
	Rook rook(EPieceColor::Black);

	if (bishop.CanMove(startPos, endPos, board) == false && rook.CanMove(startPos, endPos, board) == false)
		return false;

	return true;
}

PositionList Queen::GetPossibleMoves(Position piecePos, const Board& board)
{
    PositionList possibleMoves;
	EPieceColor pieceColor = GetColor();
	auto localBoard = board.GetBoard();

	// rook direction

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

	i = piecePos.second + 1;
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

	i = piecePos.second - 1;
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

	//bishop direction

	int currentRow = piecePos.first - 1;
	int currentCol = piecePos.second + 1;

	while (currentCol <= 8 && currentRow >= 1)
	{

		if (!(board.GetBoard()[currentRow][currentCol] == nullptr || board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor()))
			break;

		if (board.GetBoard()[currentRow][currentCol] != nullptr && board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor())
		{
			possibleMoves.push_back(Position(currentRow, currentCol));
			break;
		}

		possibleMoves.push_back(Position(currentRow, currentCol));
		currentRow--;
		currentCol++;
	}

	currentRow = piecePos.first + 1;
	currentCol = piecePos.second + 1;

	while (currentCol <= 8 && currentRow <= 8)
	{
		if (!(board.GetBoard()[currentRow][currentCol] == nullptr || board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor()))
			break;

		if (board.GetBoard()[currentRow][currentCol] != nullptr && board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor())
		{
			possibleMoves.push_back(Position(currentRow, currentCol));
			break;
		}

		possibleMoves.push_back(Position(currentRow, currentCol));
		currentRow++;
		currentCol++;
	}

	currentRow = piecePos.first + 1;
	currentCol = piecePos.second - 1;

	while (currentCol >= 1 && currentRow <= 8)
	{
		if (!(board.GetBoard()[currentRow][currentCol] == nullptr || board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor()))
			break;

		if (board.GetBoard()[currentRow][currentCol] != nullptr && board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor())
		{
			possibleMoves.push_back(Position(currentRow, currentCol));
			break;
		}

		possibleMoves.push_back(Position(currentRow, currentCol));

		currentRow++;
		currentCol--;
	}

	currentRow = piecePos.first - 1;
	currentCol = piecePos.second - 1;

	while (currentCol >= 1 && currentRow >= 1)
	{
		if (!(board.GetBoard()[currentRow][currentCol] == nullptr || board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor()))
			break;

		if (board.GetBoard()[currentRow][currentCol] != nullptr && board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor())
		{
			possibleMoves.push_back(Position(currentRow, currentCol));
			break;
		}

		possibleMoves.push_back(Position(currentRow, currentCol));

		currentRow--;
		currentCol--;
	}

    return PositionList();
}