#include "Rook.h"
#include "Board.h"

Rook::Rook(EPieceColor color)
	: Piece(EPieceType::Rook, color)
{

}

bool Rook::CanMove(Position startPos, Position endPos, const Board& board)
{
	SetPossibleMoves(startPos, board);
	if (std::find(m_possibleMoves.begin(), m_possibleMoves.end(), endPos) != m_possibleMoves.end())
		return true;

	return false;
}

void Rook::SetPossibleMoves(Position piecePos, const Board& board)
{
	EPieceColor pieceColor = GetColor();
	auto localBoard = board.GetBoard();

	//vertical down
	int i = piecePos.first + 1;
	while (i <= 8)
	{
		if (localBoard[i][piecePos.second] != nullptr)
		{
			if (localBoard[i][piecePos.second]->GetColor() != pieceColor)
				m_possibleMoves.push_back(Position(i, piecePos.second));
			break;
		}
		else
			m_possibleMoves.push_back(Position(i, piecePos.second));
		i++;
	}

	//horizontal left
	i = piecePos.second - 1;
	while (i >= 1)
	{
		if (localBoard[piecePos.first][i] != nullptr)
		{
			if (localBoard[piecePos.first][i]->GetColor() != pieceColor)
				m_possibleMoves.push_back(Position(piecePos.first, i));
			break;
		}
		else
			m_possibleMoves.push_back(Position(piecePos.first, i));
		i--;
	}

	//vertical up
	i = piecePos.first - 1;
	while (i >= 1)
	{

		if (localBoard[i][piecePos.second] != nullptr)
		{
			if (localBoard[i][piecePos.second]->GetColor() != pieceColor)
				m_possibleMoves.push_back(Position(i, piecePos.second));
			break;
		}
		else
			m_possibleMoves.push_back(Position(i, piecePos.second));
		i--;
	}

	//horizontal right
	i = piecePos.second + 1;
	while (i <= 8)
	{
		if (localBoard[piecePos.first][i] != nullptr)
		{
			if (localBoard[piecePos.first][i]->GetColor() != pieceColor)
				m_possibleMoves.push_back(Position(piecePos.first, i));
			break;
		}
		else
			m_possibleMoves.push_back(Position(piecePos.first, i));
		i++;
	}
}