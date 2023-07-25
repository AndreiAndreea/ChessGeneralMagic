#include <gtest/gtest.h>

#include "Rook.h"
#include "Board.h"

class RookTest : public testing::Test
{
	void SetUp() override
	{
		rok = new Rook(EPieceColor::White);
	}

	void TearDown() override
	{
		delete rok;
	}

protected:
	Rook* rok;
};

TEST_F(RookTest, InvalidMovement)
{
	Board board;
	Position startPos(1, 1);
	Position endPos(1, 6);
	EXPECT_FALSE(rok->CanMove(startPos, endPos, false, board));
}

TEST_F(RookTest, ValidMovement1)
{
	Board board;
	Position startPos(2, 1);
	Position endPos(6, 2);
	EXPECT_FALSE(rok->CanMove(startPos, endPos, false, board));
}

TEST_F(RookTest, ValidMovement2)
{
	Board board;
	Position startPos(6, 3);
	Position endPos(2, 3);
	EXPECT_TRUE(rok->CanMove(startPos, endPos, false, board));
}

//move in the same spot
TEST_F(RookTest, InvalidMovement2)
{
	Board board;
	Position startPos(2, 3);
	Position endPos(2, 3);
	EXPECT_FALSE(rok->CanMove(startPos, endPos, false, board));
}

TEST_F(RookTest, InvalidMovement1)
{
	Board board;
	Position startPos(5, 7);
	Position endPos(7,7);
	EXPECT_FALSE(rok->CanMove(startPos, endPos, false, board));
}