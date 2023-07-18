#include "gtest/gtest.h"

#include "Board.h"

//is not in check
TEST(BoardTest, ValidMove)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(2, 2), EPieceColor::White, EPieceType::Queen);
	board.SetPiece(Position(3, 3), EPieceColor::Black, EPieceType::Bishop);

	auto ceva = board.IsKingLeftInCheck(Position(3, 3), Position(4, 4), EPieceColor::Black);
	EXPECT_FALSE(ceva);
}

//is in check PROBLEMA
TEST(BoardTest, AttackQueen)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(2, 2), EPieceColor::White, EPieceType::Queen);
	board.SetPiece(Position(3, 3), EPieceColor::Black, EPieceType::Bishop);

	auto ceva = board.IsKingLeftInCheck(Position(3, 3), Position(4,3), EPieceColor::Black);
	EXPECT_TRUE(ceva);
}

//is in check
TEST(BoardTest, AttackRook)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(2, 5), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Rook);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(3, 5), Position(3, 4), EPieceColor::Black));
}

//is in check by pawn PROBLEMA
TEST(BoardTest, PawnAttack)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(6, 4), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Rook);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(3, 5), Position(3, 4), EPieceColor::Black));
}

//is not in check by pawn
TEST(BoardTest, PawnAttack2)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(4, 4), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_FALSE(board.IsKingLeftInCheck(Position(3, 5), Position(4, 4), EPieceColor::Black));
}

//is in check by knight
TEST(BoardTest, KnightAttack)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 4), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(3, 5), Position(4, 4), EPieceColor::Black));
}

//is not in check by knight
TEST(BoardTest, KnightAttack2)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 4), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(4, 5), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_FALSE(board.IsKingLeftInCheck(Position(4, 5), Position(3, 4), EPieceColor::Black));
}

//is in check by 2 knights, one is taken
TEST(BoardTest, KnightAttack3)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 4), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(4, 3), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(4, 5), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(4, 5), Position(3, 4), EPieceColor::Black));
}

//is in check by queen and rook, one is taken
TEST(BoardTest, QueenRookAttack)
{
	Board board;

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(2, 8), EPieceColor::White, EPieceType::Queen);
	board.SetPiece(Position(5, 2), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(3, 7), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(3, 7), Position(2, 8), EPieceColor::Black));
}