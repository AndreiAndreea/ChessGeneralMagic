#include "Knight.h"
#include "Board.h"

Knight::Knight(EPieceColor color)
    :Piece(EPieceType::Knight,color)
{

}

bool Knight::CanMove(Position startPos, Position endPos, const Board& board)
{
	EPieceColor currentColor = GetColor();
    BoardType localBoard = board.GetBoard();
	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

    if (abs(startPos.first - endPos.first) == 2 && abs(startPos.second - endPos.second) == 1 || abs(startPos.first - endPos.first) == 1 && abs(startPos.second - endPos.second) == 2)
        return true;
    return false;
}

void Knight::SetPossibleMoves(Position piecePos, std::vector<Position>& possibleMoves, const Board& board)
{
    possibleMoves.clear();

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
}

