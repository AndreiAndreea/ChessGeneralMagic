#include "gtest/gtest.h"

#include "Board.h"

TEST(IsCheckmate, KingIsNotInCheck)
{
	Board board(0);
	board.SetPiece(Position(7, 7), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(2, 4), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(5, 7), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(2, 5), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(3, 4), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(4, 4), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(4, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(3, 6), EPieceColor::White, EPieceType::Pawn);

	auto ceva = board.IsCheckmate(EPieceColor::Black);
	EXPECT_FALSE(ceva);
}

TEST(IsCheckmate, KingIsNotInCheck1)
{
	Board board(0);
	board.SetPiece(Position(7,7), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(2, 4), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(5, 7), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(2, 5), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(4, 4), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(4, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(3, 6), EPieceColor::White, EPieceType::Pawn);

	auto ceva = board.IsCheckmate(EPieceColor::Black);
	EXPECT_FALSE(ceva);
}

TEST(IsCheckmate, InvalidMove1) {

	ConfigMatrix m = { 
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', 'r', '-', '-', '-', '-', '-', '-'},
	{'b', '-', '-', '-', 'k', '-', '-', 'r'}
	};

	Board board(m);
	EXPECT_FALSE(board.IsCheckmate(EPieceColor::White));
}

