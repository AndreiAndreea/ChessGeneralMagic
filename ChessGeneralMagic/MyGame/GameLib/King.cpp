#include "King.h"
#include "Board.h"

King::King(EPieceColor color)
	: Piece(EPieceType::King, color)
{

}

bool King::VerifyKingMovmentCheck(Position startPos, Position endPos, Board board)
{
	PieceMatrix localBoard = board.GetBoard();
	EPieceColor kingColor = GetColor();

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			board.SetPiece(endPos, kingColor, EPieceType::King);
			if (localBoard[i][j] && (localBoard[i][j]->GetColor() != kingColor) && (localBoard[i][j]->GetType() != EPieceType::King) && localBoard[i][j]->CanMove(Position(i, j), endPos, board))
				return true;
			board.GetBoard()[endPos.first][endPos.second] = nullptr;
		}
	}
	return false;
}

bool King::CanMove(Position startPos, Position endPos, const Board& board)
{
	SetPossibleMoves(startPos, board);
	if (std::find(m_possibleMoves.begin(), m_possibleMoves.end(), endPos) != m_possibleMoves.end())
		return true;

	return false;
}

void King:: SetPossibleMoves(Position piecePos, const Board& board)
{

	for(int i=piecePos.first-1;i<=piecePos.first+1 ;i++)
		for (int j = piecePos.second - 1; j <= piecePos.second + 1 ; j++)
		{
			if (i >= 1 && i <= 8 && j <= 8 && j >= 1)
			{
				if (board.GetBoard()[i][j] != nullptr && board.GetBoard()[i][j]->GetColor() != GetColor() && !VerifyKingMovmentCheck(piecePos, Position(i, j), board))
					m_possibleMoves.push_back(Position(i, j));
				if (board.GetBoard()[i][j] == nullptr && !VerifyKingMovmentCheck(piecePos, Position(i, j), board))
					m_possibleMoves.push_back(Position(i, j));
			}
			
		}
}