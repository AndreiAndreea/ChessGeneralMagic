#include "gtest/gtest.h"

#include "King.h"
#include "Board.h"

class KingTest : public testing::Test {

	void SetUp() override
	{
		king = new King(EPieceColor::White);
	}

	void TearDown() override
	{
		delete king;
	}

protected:
	King* king;

};

TEST_F(KingTest, ValidMove) {
	Board board;

	Position startPos(4, 4);
	Position endPos(3, 4);
	bool canMove = king->CanMove(startPos, endPos, board);

	EXPECT_TRUE(canMove);
}

TEST_F(KingTest, ValidMove2) {
	Board board;

	Position startPos(4, 4);
	Position endPos(5, 3);
	bool canMove = king->CanMove(startPos, endPos, board);

	EXPECT_TRUE(canMove);
}


TEST_F(KingTest, InvalidMove) {
	Board board;

	Position startPos(4, 4);
	Position endPos(2, 5);
	bool canMove = king->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}

TEST_F(KingTest, InvalidMove2) {
	Board board;

	Position startPos(4, 4);
	Position endPos(6, 6);
	bool canMove = king->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}

TEST_F(KingTest, InvalidMove3) {
	Board board;

	Position startPos(1, 4);
	Position endPos(1, 5);
	bool canMove = king->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}