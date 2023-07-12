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
	Position pos1(1, 1);
	Position pos2(1, 6);
	EXPECT_FALSE(rok->CanMove(pos1, pos2, board));
}

TEST_F(RookTest, InvalidMovement2)
{
	Board board;
	Position pos1(2, 1);
	Position pos2(6, 2);
	EXPECT_FALSE(rok->CanMove(pos1, pos2, board));
}

TEST_F(RookTest, ValidMovement)
{
	Board board;
	Position pos1(6, 3);
	Position pos2(2, 3);
	EXPECT_TRUE(rok->CanMove(pos1, pos2, board));
}