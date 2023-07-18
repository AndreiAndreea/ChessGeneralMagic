#include "Pawn.h"
#include "Board.h"


Pawn::Pawn(EPieceColor color)
	: Piece(EPieceType::Pawn, color)
{

}

bool Pawn::CanMove(Position startPos, Position endPos, const Board& board)
{
	SetPossibleMoves(startPos, board);
	if (std::find(m_possibleMoves.begin(), m_possibleMoves.end(), endPos) != m_possibleMoves.end())
		return true;

	return false;
}

void Pawn:: SetPossibleMoves(Position piecePos, const Board& board)
{
	//check pawn threat
	if (GetColor() == EPieceColor::White)
	{
		if (piecePos.first + 1 <= 8)
		{
			if (board.GetBoard()[piecePos.first + 1][piecePos.second] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second]->GetColor() != GetColor())
				m_possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second));
			if(board.GetBoard()[piecePos.first + 1][piecePos.second] == nullptr)
				m_possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second));

			if(piecePos.second+1<=8)
			if (board.GetBoard()[piecePos.first+1][piecePos.second+1] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second+1]->GetColor() != GetColor())
				m_possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second+1));

			if (piecePos.second - 1 >=1)
				if (board.GetBoard()[piecePos.first + 1][piecePos.second - 1] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second - 1]->GetColor() != GetColor())
					m_possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second - 1));

			//verify for lines 2
			if (piecePos.first == 2)
			{
				if (board.GetBoard()[piecePos.first + 2][piecePos.second] != nullptr && board.GetBoard()[piecePos.first + 2][piecePos.second]->GetColor() != GetColor())
					m_possibleMoves.push_back(Position(piecePos.first + 2, piecePos.second));
				if(board.GetBoard()[piecePos.first + 2][piecePos.second] == nullptr)
					m_possibleMoves.push_back(Position(piecePos.first + 2, piecePos.second));
			}
		}
	}

	if (GetColor() == EPieceColor::Black)
	{
		if (piecePos.first - 1 >=1)
		{
			if (board.GetBoard()[piecePos.first - 1][piecePos.second] != nullptr && board.GetBoard()[piecePos.first - 1][piecePos.second]->GetColor() != GetColor())
				m_possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second));
			if (board.GetBoard()[piecePos.first - 1][piecePos.second] == nullptr)
				m_possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second));

			if (piecePos.second + 1 <= 8)
				if (board.GetBoard()[piecePos.first - 1][piecePos.second + 1] != nullptr && board.GetBoard()[piecePos.first - 1][piecePos.second + 1]->GetColor() != GetColor())
					m_possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second + 1));

			if (piecePos.second - 1 >= 1)
				if (board.GetBoard()[piecePos.first - 1][piecePos.second - 1] != nullptr && board.GetBoard()[piecePos.first - 1][piecePos.second - 1]->GetColor() != GetColor())
					m_possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second - 1));

			//verify for lines 7
			if (piecePos.first == 7)
			{
				if (board.GetBoard()[piecePos.first - 2][piecePos.second] != nullptr && board.GetBoard()[piecePos.first - 2][piecePos.second]->GetColor() != GetColor())
					m_possibleMoves.push_back(Position(piecePos.first - 2, piecePos.second));
				if (board.GetBoard()[piecePos.first - 2][piecePos.second] == nullptr)
					m_possibleMoves.push_back(Position(piecePos.first - 2, piecePos.second));
			}
		}
	}

}