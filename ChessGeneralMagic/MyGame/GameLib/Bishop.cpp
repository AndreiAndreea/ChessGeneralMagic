#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(EPieceColor color)
	: Piece(EPieceType::Bishop, color)
{

}

bool Bishop::CanMove(Position startPos, Position endPos, const Board& board)
{
	auto possibleMoves = GetPossibleMoves(startPos, board);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
		return true;

	return false;
}

//create a vector with all of the possible moves of a piece
PositionList Bishop::GetPossibleMoves(Position piecePos, const Board& board)
{
	PositionList possibleMoves;
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