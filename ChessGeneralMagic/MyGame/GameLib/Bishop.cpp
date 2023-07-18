#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(EPieceColor color)
	: Piece(EPieceType::Bishop, color)
{

}

bool Bishop::CanMove(Position startPos, Position endPos, const Board& board)
{
	SetPossibleMoves(startPos, board);
	if (std::find(m_possibleMoves.begin(), m_possibleMoves.end(), endPos) != m_possibleMoves.end())
		return true;

	return false;
}

//create a vector with all of the possible moves of a piece
void Bishop::SetPossibleMoves(Position piecePos, const Board& board)
{
	int currentRow = piecePos.first - 1;
	int currentCol = piecePos.second + 1;

	while (currentCol <= 8 && currentRow >= 1)
	{
	
		if (!(board.GetBoard()[currentRow][currentCol] == nullptr || board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor()))
			break;

		if (board.GetBoard()[currentRow][currentCol] != nullptr && board.GetBoard()[currentRow][currentCol]->GetColor() != GetColor())
		{
			m_possibleMoves.push_back(Position(currentRow, currentCol));
			break;
		}

		m_possibleMoves.push_back(Position(currentRow, currentCol));
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
			m_possibleMoves.push_back(Position(currentRow, currentCol));
			break;
		}

		m_possibleMoves.push_back(Position(currentRow, currentCol));
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
			m_possibleMoves.push_back(Position(currentRow, currentCol));
			break;
		}

		m_possibleMoves.push_back(Position(currentRow, currentCol));

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
			m_possibleMoves.push_back(Position(currentRow, currentCol));
			break;
		}

		m_possibleMoves.push_back(Position(currentRow, currentCol));

		currentRow--;
		currentCol--;
	}

}