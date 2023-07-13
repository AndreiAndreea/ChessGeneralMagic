//#include "gtest/gtest.h"
//
//#include "Knight.h"
//#include "Board.h"
//
//class KnightTest : public testing::Test
//{
//	void SetUp() override
//	{
//		knight = new Knight(EPieceColor::White);
//	}
//
//	void TearDown() override
//	{
//		delete knight;
//	}
//
//protected:
//	Knight* knight;
//};
//
//TEST_F(KnightTest, ValidMovement)
//{
//	Board board;
//	Position startPos(6, 3);
//	Position endPos(8, 2);
//	EXPECT_TRUE(knight->CanMove(startPos, endPos, board));
//}
//
//TEST_F(KnightTest, ValidMovement2)
//{
//	Board board;
//	Position startPos(6, 3);
//	Position endPos(4, 2);
//	EXPECT_TRUE(knight->CanMove(startPos, endPos, board));
//}
//
//TEST_F(KnightTest, InvalidMovement)
//{
//	Board board;
//	Position startPos(6, 3);
//	Position endPos(4, 1);
//	EXPECT_FALSE(knight->CanMove(startPos, endPos, board));
//}
//
