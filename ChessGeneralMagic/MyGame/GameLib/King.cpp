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

	bool can;
	can = localBoard[7][4]->CanMove(Position(7, 4), endPos, board);

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			board.SetPiece(endPos, kingColor, EPieceType::King);
			if ((localBoard[i][j] != nullptr) && (localBoard[i][j]->GetColor() != kingColor) && (localBoard[i][j]->GetType() != EPieceType::King) && (localBoard[i][j]->CanMove(Position(i, j), endPos, board) == 1))
				return true;
			board.GetBoard()[endPos.first][endPos.second] = nullptr;
		}
	}
	return false;
}

bool King::CanMove(Position startPos, Position endPos, const Board& board)
{
	PositionList possibleMoves;
	possibleMoves = GetPossibleMoves(startPos, board);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
		return true;

	return false;

	/*EPieceColor currentColor = GetColor();
	PieceMatrix localBoard = board.GetBoard();
	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

	if (startPos.first == endPos.first && startPos.second == endPos.second)
		return false;

	if (std::abs(startPos.first - endPos.first) > 1 && std::abs(startPos.second - endPos.second) > 1)
		return false;

	if (VerifyKingMovmentCheck(startPos, endPos, board))
		return false;

	return true;*/
}

PositionList King:: GetPossibleMoves(Position piecePos, const Board& board)
{

	PositionList possibleMoves;

	Position futurePos;
	futurePos = piecePos;
	for(int i=piecePos.first-1;i<=piecePos.first+1 && i>=1 && i<=8;i++)
		for (int j = piecePos.second - 1; j <= piecePos.second + 1 && j <= 8 & j >= 1; j++)
		{
			if (board.GetBoard()[i][j] != nullptr && board.GetBoard()[i][j]->GetColor() != GetColor() && !VerifyKingMovmentCheck(piecePos,Position(i,j),board))
				possibleMoves.push_back(Position(i, j));
			if (board.GetBoard()[i][j] == nullptr && !VerifyKingMovmentCheck(piecePos, Position(i, j), board))
				possibleMoves.push_back(Position(i, j));
		}

	return possibleMoves;
}