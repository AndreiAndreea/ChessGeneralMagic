#include "Pawn.h"
#include "Board.h"


Pawn::Pawn(EPieceColor color)
	: Piece(EPieceType::Pawn, color)
{

}

bool Pawn::CanMove(Position startPos, Position endPos, const Board& board)
{

	EPieceColor currentColor = GetColor();
	PieceMatrix localBoard = board.GetBoard();
	if (localBoard[endPos.first][endPos.second] != nullptr && currentColor == localBoard[endPos.first][endPos.second]->GetColor())
		return false;

	//checking the direction of the movement
	if (currentColor == EPieceColor::White)
	{
		if (startPos.first >= endPos.first)
			return false;
	}
	else
	{
		if (startPos.first <= endPos.first)
			return false;
	}

	if (std::abs(startPos.first - endPos.first) == 2)
	{
		if ((startPos.first != 7 && startPos.first != 2))
			return false;

		if (localBoard[endPos.first][endPos.second] != nullptr)
			return false;
	}


	if (std::abs(startPos.first - endPos.first) > 2)
		return false;

	//diagonally
	if (endPos.second != startPos.second)
		if (std::abs(endPos.second != startPos.second) > 1)
			return false;
		else
			if (localBoard[endPos.first][endPos.second] == nullptr)

				return false;

	if (std::abs(startPos.first - endPos.first) > 2)
		return false;

    return true;
}

void Pawn::SetPossibleMoves(Position piecePos, std::vector<Position>& possibleMoves, const Board& board)
{
	possibleMoves.clear();

	//check pawn threat
	if (GetColor() == EPieceColor::White)
	{
		if (piecePos.first + 1 <= 8)
		{
			if (board.GetBoard()[piecePos.first + 1][piecePos.second] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second]->GetColor() != GetColor())
				possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second));
			if(board.GetBoard()[piecePos.first + 1][piecePos.second] == nullptr)
				possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second));

			if(piecePos.second+1<=8)
			if (board.GetBoard()[piecePos.first+1][piecePos.second+1] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second+1]->GetColor() != GetColor())
				possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second+1));

			if (piecePos.second - 1 >=1)
				if (board.GetBoard()[piecePos.first + 1][piecePos.second - 1] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second - 1]->GetColor() != GetColor())
					possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second - 1));

			//verify for lines 2
			if (piecePos.first == 2)
			{
				if (board.GetBoard()[piecePos.first + 2][piecePos.second] != nullptr && board.GetBoard()[piecePos.first + 2][piecePos.second]->GetColor() != GetColor())
					possibleMoves.push_back(Position(piecePos.first + 2, piecePos.second));
				if(board.GetBoard()[piecePos.first + 2][piecePos.second] == nullptr)
					possibleMoves.push_back(Position(piecePos.first + 2, piecePos.second));
			}
		}
	}

	//if (GetColor() == EPieceColor::Black)
	//{
	//	if (piecePos.first - 1 >=1)
	//	{
	//		if (board.GetBoard()[piecePos.first - 1][piecePos.second] != nullptr && board.GetBoard()[piecePos.first - 1][piecePos.second]->GetColor() != GetColor())
	//			possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second));
	//		if (board.GetBoard()[piecePos.first + 1][piecePos.second] == nullptr)
	//			possibleMoves.push_back(Position(piecePos.first - 1, piecePos.second));

	//		if (piecePos.second + 1 <= 8)
	//			if (board.GetBoard()[piecePos.first + 1][piecePos.second + 1] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second + 1]->GetColor() != GetColor())
	//				possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second + 1));

	//		if (piecePos.second - 1 >= 1)
	//			if (board.GetBoard()[piecePos.first + 1][piecePos.second - 1] != nullptr && board.GetBoard()[piecePos.first + 1][piecePos.second - 1]->GetColor() != GetColor())
	//				possibleMoves.push_back(Position(piecePos.first + 1, piecePos.second - 1));

	//		//verify for lines 2
	//		if (piecePos.first == 2)
	//		{
	//			if (board.GetBoard()[piecePos.first + 2][piecePos.second] != nullptr && board.GetBoard()[piecePos.first + 2][piecePos.second]->GetColor() != GetColor())
	//				possibleMoves.push_back(Position(piecePos.first + 2, piecePos.second));
	//			if (board.GetBoard()[piecePos.first + 2][piecePos.second] == nullptr)
	//				possibleMoves.push_back(Position(piecePos.first + 2, piecePos.second));
	//		}
	//	}
	//}
}
