#include "King.h"
#include "Board.h"


King::King(EPieceColor color) 
    : Piece(EPieceType::King, color)
{

}

bool King::VerifyKingMovmentCheck(Position startPos, Position endPos, const Board& board)
{
	BoardType localBoard = board.GetBoard();
	EPieceColor kingColor = GetColor();

	for (int i = 1; i <=8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			auto culoare = localBoard[i][j]->GetColor();
			auto can = localBoard[i][j]->CanMove(Position(i, j), endPos, board);
			if ((localBoard[i][j] != nullptr) && (culoare != kingColor) && (can == 1) && (localBoard[i][j]->GetType() != EPieceType::King));
				return true;
		}
	}
	return false;
}

bool King::CanMove(Position startPos, Position endPos, const Board& board)
{
	EPieceColor currentColor = GetColor();
	BoardType localBoard = board.GetBoard();
	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

	if (startPos.first == endPos.first && startPos.second == endPos.second)
		return false;

	if (std::abs(startPos.first - endPos.first) > 1 && std::abs(startPos.second - endPos.second) > 1)
		return false;

	if (VerifyKingMovmentCheck(startPos, endPos, board))
		return false;

    return true;
}

