#include "gtest/gtest.h"

#include "Board.h"

TEST(IsCheckmate, KingIsNotInCheck)
{
	Board board;

	board.SetPiece(Position(4, 6), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 5), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(6, 8), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(3, 6), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(4, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(5, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(5, 6), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(4, 7), EPieceColor::White, EPieceType::Pawn);

	auto ceva = board.IsCheckmate(EPieceColor::Black);
	EXPECT_FALSE(ceva);
}

TEST(IsCheckmate, KingIsNotInCheck1)
{
	Board board;

	board.SetPiece(Position(4, 6), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 5), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(6, 8), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(3, 6), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(5, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(5, 6), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(4, 7), EPieceColor::White, EPieceType::Pawn);

	auto ceva = board.IsCheckmate(EPieceColor::Black);
	EXPECT_FALSE(ceva);
}

