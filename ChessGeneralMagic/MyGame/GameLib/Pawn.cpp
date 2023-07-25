#include "Pawn.h"
#include "Board.h"


Pawn::Pawn(EPieceColor color)
	: Piece(EPieceType::Pawn, color)
{

}

bool Pawn::CanMove(Position startPos, Position endPos, bool isKingAttacking, const Board& board)
{
	PositionList possibleMoves;
	possibleMoves = GetPossibleMoves(startPos, isKingAttacking, board);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
		return true;

	return false;
}

PositionList Pawn::GetPossibleMoves(Position piecePos, bool isKingAttacking, const Board& board)
{
	PositionList possibleMoves;

	//check pawn threat
	if (GetColor() == EPieceColor::Black)
	{
		if (piecePos.first + 1 < 8)
		{
			if (board.GetBoard()[piecePos.first + 1][piecePos.second] == nullptr)
				possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second));

			if (piecePos.second + 1 < 8)
				if (board.GetBoard()[piecePos.first + 1][piecePos.second + 1] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second + 1]->GetColor() != GetColor())
					possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second + 1));

			if (piecePos.second - 1 >= 0)
				if (board.GetBoard()[piecePos.first + 1][piecePos.second - 1] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second - 1]->GetColor() != GetColor())
					possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second - 1));

			//verify for lines 2
			if (piecePos.first == 1)
			{
				if (board.GetBoard()[piecePos.first + 1][piecePos.second] == nullptr)
				{
					if (board.GetBoard()[piecePos.first + 2][piecePos.second] == nullptr)
						possibleMoves.push_back(Position(piecePos.first + 2, piecePos.second));
				}
			}
		}
	}

	if (GetColor() == EPieceColor::White)
	{
		if (piecePos.first - 1 >= 0)
		{
			if (board.GetBoard()[piecePos.first - 1][piecePos.second] == nullptr)
				possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second));

			if (piecePos.second + 1 < 8)
				if (board.GetBoard()[piecePos.first - 1][piecePos.second + 1] && board.GetBoard()[piecePos.first - 1][piecePos.second + 1]->GetColor() != GetColor())
					possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second + 1));

			if (piecePos.second - 1 >= 0)
				if (board.GetBoard()[piecePos.first - 1][piecePos.second - 1] && board.GetBoard()[piecePos.first - 1][piecePos.second - 1]->GetColor() != GetColor())
					possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second - 1));

			//verify for lines 7
			if (piecePos.first == 6)
			{
				if (board.GetBoard()[piecePos.first - 1][piecePos.second] == nullptr)
				{
					if (board.GetBoard()[piecePos.first - 2][piecePos.second] == nullptr)
						possibleMoves.push_back(Position(piecePos.first - 2, piecePos.second));
				}
			}
		}
	}

	return possibleMoves;
}