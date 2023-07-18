#include "Knight.h"
#include "Board.h"

Knight::Knight(EPieceColor color)
	:Piece(EPieceType::Knight, color)
{

}

bool Knight::CanMove(Position startPos, Position endPos, const Board& board)
{
	SetPossibleMoves(startPos, board);
	if (std::find(m_possibleMoves.begin(), m_possibleMoves.end(), endPos) != m_possibleMoves.end())
		return true;

	return false;
}

void Knight::SetPossibleMoves(Position piecePos, const Board& board)
{

	for (int i = piecePos.first - 2; i <= piecePos.first + 2; i++)
		for (int j = piecePos.second - 2; j <= piecePos.second + 2; j++)
		{
			if (i <= 8 && i >= 1 && j <= 8 && j >= 1)
				if (abs(piecePos.first - i) == 2 && abs(piecePos.second - j) == 1 || abs(piecePos.first - i) == 1 && abs(piecePos.second - j) == 2)
				{
					if (board.GetBoard()[i][j] != nullptr && board.GetBoard()[i][j]->GetColor() != GetColor())
						m_possibleMoves.push_back(Position(i, j));
					if (board.GetBoard()[i][j] == nullptr)
						m_possibleMoves.push_back(Position(i, j));
				}
		}
}