#include "Knight.h"
#include "Board.h"

Knight::Knight(EPieceColor color)
    :Piece(EPieceType::Knight,color)
{

}

bool Knight::CanMove(Position startPos, Position endPos, const Board& board)
{
	//PositionList possibleMoves;
	//possibleMoves = GetPossibleMoves(startPos, board);
	//if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
	//	return true;

	//return false;

	EPieceColor currentColor = GetColor();
    PieceMatrix localBoard = board.GetBoard();
	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

    if (abs(startPos.first - endPos.first) == 2 && abs(startPos.second - endPos.second) == 1 || abs(startPos.first - endPos.first) == 1 && abs(startPos.second - endPos.second) == 2)
        return true;
    return false;
}

PositionList Knight:: GetPossibleMoves(Position piecePos, const Board& board)
{
	PositionList possibleMoves;

	for (int i = piecePos.first - 2; i <= piecePos.first + 2 && i <= 8 && i >= 1; i++)
		for (int j = piecePos.second - 2; j <= piecePos.second + 2 && j <= 8 && j >= 1; j++)
		{
			if (abs(piecePos.first - i) == 2 && abs(piecePos.second - j) == 1 || abs(piecePos.first - i) == 1 && abs(piecePos.second - j) == 2)
			{
				if (board.GetBoard()[i][j] != nullptr && board.GetBoard()[i][j]->GetColor() != GetColor())
					possibleMoves.push_back(Position(i, j));
				if (board.GetBoard()[i][j] == nullptr)
					possibleMoves.push_back(Position(i, j));
			}
		}

	return possibleMoves;
}