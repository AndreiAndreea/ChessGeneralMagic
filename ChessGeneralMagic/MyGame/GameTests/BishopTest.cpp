#include "gtest/gtest.h"

#include "Bishop.h"
#include "Board.h"

// Define a fixture for the Bishop tests
class BishopTest : public testing::Test {

	void SetUp() override
	{	
		bishop = new Bishop(EPieceColor::White);
	}

	void TearDown() override
	{
		delete bishop;
	}

protected:
	Bishop* bishop;

};

TEST_F(BishopTest, ValidMove) {
	Board board;
	//Bishop bishop(EPieceColor::White);

	Position startPos(2, 2);
	Position endPos(5, 5);
	bool canMove = bishop->CanMove(startPos, endPos, board);

 	EXPECT_TRUE(canMove);
}

TEST_F(BishopTest, ValidMove2) {
	Board board;
	//Bishop bishop(EPieceColor::White);

	Position startPos(4, 3);
	Position endPos(6, 5);
	bool canMove = bishop->CanMove(startPos, endPos, board);

	EXPECT_TRUE(canMove);
}

TEST_F(BishopTest, InvalidMove) {
	Board board;
	Position startPos(2, 2);
	Position endPos(4, 5);
	bool canMove = bishop->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}