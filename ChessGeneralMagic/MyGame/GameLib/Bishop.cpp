#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(EPieceColor color) 
    : Piece (EPieceType::Bishop, color)
{

}

bool Bishop::CanMove(Position startPos, Position endPos, const Board& board)
{

	EPieceColor currentColor = GetColor();

	if (startPos.first != endPos.first && startPos.second != endPos.second || (startPos.first == endPos.first && startPos.second == endPos.second))
		return false;

	BoardType localBoard = board.GetBoard();

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