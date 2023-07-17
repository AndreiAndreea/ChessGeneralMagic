#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(EPieceColor color)
	: Piece(EPieceType::Bishop, color)
{

}

bool Bishop::CanMove(Position startPos, Position endPos, const Board& board)
{

	EPieceColor currentColor = GetColor();

	BoardType localBoard = board.GetBoard();
	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

	if (std::abs(startPos.first - endPos.first) != std::abs(startPos.second - endPos.second))
		return false;

	int startRow = startPos.first;
	int startCol = startPos.second;

	int endRow = endPos.first;
	int endCol = endPos.second;

	int rowStep = (startRow < endRow) ? 1 : -1;
	int colStep = (startCol < endCol) ? 1 : -1;

	int currentRow = startRow + rowStep;
	int currentCol = startCol + colStep;

	while (currentRow != endRow && currentCol != endCol)
	{
		if (localBoard[currentRow][currentCol] != nullptr)
			return false;

		currentRow += rowStep;
		currentCol += colStep;
	}
	return true;
}

//create a vector with all of the possible moves of a piece
void Bishop::SetPossibleMoves(Position piecePos, std::vector<Position>& possibleMoves, const Board& board)
{
	possibleMoves.clear();

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
}
