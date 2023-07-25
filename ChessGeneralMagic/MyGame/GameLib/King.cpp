#include "King.h"
#include "Board.h"

King::King(EPieceColor color)
	: Piece(EPieceType::King, color)
{

}

bool King::VerifyKingMovmentCheck(Position startPos, Position endPos, const Board& board) const
{
	Board localBoard(board);
	EPieceColor kingColor = GetColor();

	localBoard.SetPiece(endPos, kingColor, EPieceType::King);
	localBoard.SetPieceToNullptr(startPos);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (localBoard.GetBoard()[i][j] && (localBoard.GetBoard()[i][j]->GetColor() != kingColor) && (localBoard.GetBoard()[i][j]->GetType() != EPieceType::King) && localBoard.GetBoard()[i][j]->CanMove(Position(i, j), endPos, true, localBoard))
				return true;
		}
	}
	localBoard.GetBoard()[endPos.first][endPos.second] = nullptr;
	localBoard.SetPiece(startPos, kingColor, EPieceType::King);
	return false;
}

bool King::CanMakeBigCastling(EPieceColor color, const Board& board) const
{
	if (color == EPieceColor::White)
	{
		if (board.GetCastlingVect()[0][0])
		{
			//check if the path is clear
			for (int i = 3; i > 0; i--)
			{
				if (board.GetBoard()[7][i] != nullptr)
					return false;
			}

			//check if king is in check on the way to the rook
			for (int i = 4; i > 0; i--)
			{
				if (board.IsKingInCheck(Position(7, i), EPieceColor::White))
					return false;
			}
			return true;
		}
		return false;
	}
	else
	{
		if (board.GetCastlingVect()[1][0])
		{
			//check if the path is clear
			for (int i = 3; i > 0; i--)
			{
				if (board.GetBoard()[0][i] != nullptr)
					return false;
			}

			//check if king is in check on the way to the rook
			for (int i = 4; i > 1; i--)
			{
				if (board.IsKingInCheck(Position(0, i), EPieceColor::Black))
					return false;
			}
			return true;
		}
		return false;
	}
}

bool King::CanMakeSmallCastling(EPieceColor color, const Board& board) const
{
	if (color == EPieceColor::White)
	{
		if (board.GetCastlingVect()[0][1])
		{
			//check if the path is clear
			for (int i = 5; i < 7; i++)
			{
				if (board.GetBoard()[7][i] != nullptr)
					return false;
			}

			//check if king is in check on the way to the rook
			for (int i = 4; i < 7; i++)
			{
				if (board.IsKingInCheck(Position(7,i),EPieceColor::White))
					return false;
			}
			return true;
		}
		return false;
	}
	else
	{
		if (board.GetCastlingVect()[1][1])
		{
			//check if the path is clear
			for (int i = 5; i < 7; i++)
			{
				if (board.GetBoard()[0][i] != nullptr)
					return false;
			}

			//check if king is in check on the way to the rook
			for (int i = 4; i < 7; i++)
			{
				if (board.IsKingInCheck(Position(0, i), EPieceColor::Black))
					return false;
			}
			return true;
		}
		return false;
	}
}

bool King::CanMove(Position startPos, Position endPos, bool isKingAttacking, const Board& board)
{
	auto possibleMoves = GetPossibleMoves(startPos, isKingAttacking, board);
	if (std::find(possibleMoves.begin(), possibleMoves.end(), endPos) != possibleMoves.end())
		return true;

	//Castling

	//auto piece = board.GetBoard()[startPos.first][startPos.second];
	//auto color = piece->GetColor();
	//if (startPos.second - endPos.second == 2)
	//	if (CanMakeBigCastling(color, board))
	//		return true;
	//if (startPos.second - endPos.second == -2)
	//	if (CanMakeSmallCastling(color, board))
	//		return true;

	return false;
}

PositionList King::GetPossibleMoves(Position piecePos, bool isKingAttacking, const Board& board)
{
	PositionList possibleMoves;

	for (int i = piecePos.first - 1; i <= piecePos.first + 1; i++)
	{
		for (int j = piecePos.second - 1; j <= piecePos.second + 1; j++)
		{
			if (i >= 0 && i < 8 && j < 8 && j >= 0)
			{
				if (board.GetBoard()[i][j] != nullptr && board.GetBoard()[i][j]->GetColor() != GetColor() && !VerifyKingMovmentCheck(piecePos, Position(i, j), board))
					possibleMoves.push_back(Position(i, j));
				if (board.GetBoard()[i][j] == nullptr && !VerifyKingMovmentCheck(piecePos, Position(i, j), board))
					possibleMoves.push_back(Position(i, j));
			}
		}
	}

	if (!isKingAttacking)
	{
		auto piece = board.GetBoard()[piecePos.first][piecePos.second];
		auto color = piece->GetColor();
		if (CanMakeBigCastling(color, board))
			possibleMoves.push_back(Position(piecePos.first ,piecePos.second -2));
		if (CanMakeSmallCastling(color, board))
			possibleMoves.push_back(Position(piecePos.first, piecePos.second + 2));
	}

	return possibleMoves;
}

