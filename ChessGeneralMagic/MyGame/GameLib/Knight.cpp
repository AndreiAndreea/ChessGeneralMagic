#include "Knight.h"
#include "Board.h"

Knight::Knight(EPieceColor color)
	:Piece(EPieceType::Knight, color)
{

}

bool Knight::CanMove(Position startPos, Position endPos, bool isKingAttacking, const Board& board)
{
	auto possibleMoves = GetPossibleMoves(startPos, isKingAttacking, board);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
		return true;

	return false;
}

PositionList Knight::GetPossibleMoves(Position piecePos, bool isKingAttacking, const Board& board)
{
	PositionList possibleMoves;

	for (int i = piecePos.first - 2; i <= piecePos.first + 2; i++)
		for (int j = piecePos.second - 2; j <= piecePos.second + 2; j++)
		{
			if (i < 8 && i >= 0 && j < 8 && j >= 0)
				if (abs(piecePos.first - i) == 2 && abs(piecePos.second - j) == 1 || abs(piecePos.first - i) == 1 && abs(piecePos.second - j) == 2)
				{
					if (!board.IsKingLeftInCheck(piecePos, { i, j }, GetColor()))
					{
						if (board.GetBoard()[i][j] != nullptr && board.GetBoard()[i][j]->GetColor() != GetColor())
							possibleMoves.push_back(Position(i, j));
						if (board.GetBoard()[i][j] == nullptr)
							possibleMoves.push_back(Position(i, j));
					}
				}
		}
	return possibleMoves;
}