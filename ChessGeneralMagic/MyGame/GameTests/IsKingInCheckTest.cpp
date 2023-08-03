#include "gtest/gtest.h"

#include "Board.h"

//is not in check
TEST(BoardTest, ValidMove)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(4, 4), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(1, 1), EPieceColor::White, EPieceType::Queen);
	board.SetPiece(Position(2, 2), EPieceColor::Black, EPieceType::Bishop);

	auto ceva = board.IsKingLeftInCheck(Position(3, 3), Position(4, 4), EPieceColor::Black);
	EXPECT_FALSE(ceva);
}

//is in check 
TEST(BoardTest, AttackQueen)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(4,4), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(2, 2), EPieceColor::White, EPieceType::Queen);
	board.SetPiece(Position(3, 3), EPieceColor::Black, EPieceType::Bishop);

	auto ceva = board.IsKingLeftInCheck(Position(3, 3), Position(4, 3), EPieceColor::Black);
	EXPECT_TRUE(ceva);
}

//is in check
TEST(BoardTest, AttackRook)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(2, 5), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Rook);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(3, 5), Position(3, 4), EPieceColor::Black));
}

//is in check by pawn
TEST(BoardTest, PawnAttack)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(6, 4), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Rook);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(3, 5), Position(3, 4), EPieceColor::Black));
}

//is not in check by pawn
TEST(BoardTest, PawnAttack2)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(4, 4), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_FALSE(board.IsKingLeftInCheck(Position(3, 5), Position(4, 4), EPieceColor::Black));
}

//is in check by knight
TEST(BoardTest, KnightAttack)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);


	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 4), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(3, 5), Position(4, 4), EPieceColor::Black));
}

//is not in check by knight
TEST(BoardTest, KnightAttack2)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 4), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(4, 5), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_FALSE(board.IsKingLeftInCheck(Position(4, 5), Position(3, 4), EPieceColor::Black));
}

//is in check by 2 knights, one is taken
TEST(BoardTest, KnightAttack3)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 4), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(4, 3), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(4, 5), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(4, 5), Position(3, 4), EPieceColor::Black));
}

//is in check by queen and rook, one is taken
TEST(BoardTest, QueenRookAttack)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(4, 4), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(1, 7), EPieceColor::White, EPieceType::Queen);
	board.SetPiece(Position(4, 1), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(2, 6), EPieceColor::Black, EPieceType::Bishop);

	EXPECT_TRUE(board.IsKingLeftInCheck(Position(2, 6), Position(1, 7), EPieceColor::Black));
}

TEST(BoardTest, QueenRookAttack1)
{
	ConfigMatrix m = {
				/*0    1    2    3    4    5    6    7*/
		/*0*/	{'-', '-', '-', 'Q', 'K', 'B', '-', '-'},
		/*1*/	{'-', '-', '-', 'P', 'P', '-', '-', '-'},
		/*2*/	{'-', '-', '-', '-', '-', '-', '-', '-'},
		/*3*/	{'-', '-', '-', '-', '-', '-', '-', 'q'},
		/*4*/	{'-', '-', '-', '-', '-', '-', '-', '-'},
		/*5*/	{'-', '-', '-', '-', '-', '-', '-', '-'},
		/*6*/	{'-', '-', '-', '-', '-', '-', '-', '-'},
		/*7*/	{'-', '-', '-', 'k', '-', '-', '-', '-'}
	};

	Board board(m);

	EXPECT_TRUE(board.IsCheckmate(EPieceColor::Black));
}

TEST(BoardTest, BoardDeveloped)
{
	Board board(0);
	board.SetPiece(Position(0, 0), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(1, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(1, 6), EPieceColor::Black, EPieceType::Bishop);
	board.SetPiece(Position(2, 4), EPieceColor::Black, EPieceType::Pawn);
	board.SetPiece(Position(2, 6), EPieceColor::White, EPieceType::Knight);
	board.SetPiece(Position(4, 7), EPieceColor::Black, EPieceType::Queen);
	board.SetPiece(Position(5, 3), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(5, 4), EPieceColor::Black, EPieceType::Knight);
	board.SetPiece(Position(1, 7), EPieceColor::Black, EPieceType::Knight);
	board.SetPiece(Position(5, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(2, 7), EPieceColor::Black, EPieceType::Pawn);

	EXPECT_FALSE(board.IsKingLeftInCheck(Position(2, 6), Position(7, 7), EPieceColor::Black));
}

TEST(BoardTest, BoardDeveloped1)
{
	Board board(0);
	board.SetPiece(Position(7, 7), EPieceColor::White, EPieceType::King);

	board.SetPiece(Position(0, 4), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(1, 4), EPieceColor::Black, EPieceType::Pawn);
	board.SetPiece(Position(0, 3), EPieceColor::Black, EPieceType::Queen);
	board.SetPiece(Position(0, 6), EPieceColor::Black, EPieceType::Knight);
	board.SetPiece(Position(1, 3), EPieceColor::Black, EPieceType::Pawn);
	board.SetPiece(Position(0, 5), EPieceColor::Black, EPieceType::Bishop);
	board.SetPiece(Position(2, 6), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(3, 7), EPieceColor::White, EPieceType::Queen);

	EXPECT_FALSE(board.IsKingLeftInCheck(Position(0, 6), Position(2, 5), EPieceColor::Black));
}

TEST(BoardTest, BoardDeveloped2)
{
	Board board;

	board.SetPiece(Position(2, 5), EPieceColor::Black, EPieceType::Queen);
	board.SetPiece(Position(4, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(5,2), EPieceColor::Black, EPieceType::Bishop);
	board.SetPiece(Position(5, 7), EPieceColor::Black, EPieceType::Knight);
	board.SetPiece(Position(5, 3), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(5, 6), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(6,6), EPieceColor::White, EPieceType::Knight);

	EXPECT_FALSE(board.IsKingLeftInCheck(Position(7, 1), Position(6, 1), EPieceColor::White));
}