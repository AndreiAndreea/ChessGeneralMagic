#include "Queen.h"
#include "Board.h"

Queen::Queen(EPieceColor color) 
    : Piece(EPieceType::Queen,color)
{

}

bool Queen::CanMove(Position startPos, Position endPos, const Board& board)
{
	auto ceva = board.GetBoard()[startPos.first][startPos.second]->GetColor();
	Bishop bishop(ceva);
	Rook rook(board.GetBoard()[startPos.first][startPos.second]->GetColor());

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
	while (i < 8)
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
	while (i >= 0)
	{
		if (localBoard[piecePos.first][i] != nullptr)
		{
			if (localBoard[piecePos.first][i]->GetColor() != pieceColor)
				possibleMoves.push_back(Position(piecePos.first,i));
			break;
		}
		else
			possibleMoves.push_back(Position( piecePos.first,i));
		i--;
	}

	i = piecePos.first - 1;
	while (i >= 0)
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
	while (i < 8)
	{
		if (localBoard[piecePos.first][i] != nullptr)
		{
			if (localBoard[piecePos.first][i]->GetColor() != pieceColor)
				possibleMoves.push_back(Position(piecePos.first,i));
			break;
		}
		else
			possibleMoves.push_back(Position(piecePos.first, i));
		i++;
	}



	//bishop direction

	//diagonally upwards right
	int currentRow = piecePos.first - 1;
	int currentCol = piecePos.second + 1;

	while (currentCol < 8 && currentRow >= 0)
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

	//diagonally downwards right
	currentRow = piecePos.first + 1;
	currentCol = piecePos.second + 1;

	while (currentCol < 8 && currentRow < 8)
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

	//diagonally downwards left
	currentRow = piecePos.first + 1;
	currentCol = piecePos.second - 1;

	while (currentCol >= 0 && currentRow < 8)
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

	//diagonally upwards left
	currentRow = piecePos.first - 1;
	currentCol = piecePos.second - 1;

	while (currentCol >= 0 && currentRow >= 0)
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

	return possibleMoves;
}