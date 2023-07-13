#include "gtest/gtest.h"

#include "Board.h"


TEST( BoardTest , ValodMove)
{
	Board board;
	BoardType curentBoard = board.GetBoard();

	board.GetBoard()[5][5] = std::make_shared<King>(EPieceColor::Black);
	board.GetBoard()[2][2] = std::make_shared<Queen>(EPieceColor::White);
	board.GetBoard()[3][3] = std::make_shared<Bishop>(EPieceColor::Black);
	auto ceva =board.IsKingInCheck(Position(3, 3), Position(4, 4), EPieceColor::Black);
	EXPECT_TRUE(ceva);
}

TEST(BoardTest, FalseQueen)
{
	Board board;
	BoardType curentBoard = board.GetBoard();

	board.GetBoard()[5][5] = std::make_shared<King>(EPieceColor::Black);
	board.GetBoard()[2][2] = std::make_shared<Queen>(EPieceColor::White);
	board.GetBoard()[3][3] = std::make_shared<Bishop>(EPieceColor::Black);
	auto ceva = board.IsKingInCheck(Position(3, 3), Position(2, 4), EPieceColor::Black);
	EXPECT_FALSE(ceva);
}

//TEST(BoardTest, FalseRook)
//{
//	Board board;
//	BoardType curentBoard = board.GetBoard();
//
//	curentBoard[5][5] = std::make_shared<King>(EPieceColor::Black);
//	curentBoard[2][5] = std::make_shared<Rook>(EPieceColor::White);
//	curentBoard[3][5] = std::make_shared<Rook>(EPieceColor::Black);
//
//	EXPECT_FALSE(board.IsKingInCheck(Position(3, 5), Position(3, 4), EPieceColor::Black));
//}