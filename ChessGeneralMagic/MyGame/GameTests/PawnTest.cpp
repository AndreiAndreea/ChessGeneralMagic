#include "gtest/gtest.h"

#include "Pawn.h"
#include "Board.h"

class PawnTest : public testing::Test {

	void SetUp() override
	{
		pawn = new Pawn(EPieceColor::Black);
	}

	void TearDown() override
	{
		delete pawn;
	}

protected:
	Pawn* pawn;

};


//moving upwards 2 spots
TEST_F(PawnTest, ValidMove) {
	Board board;

	Position startPos(7, 2);
	Position endPos(5, 2);
	bool canMove = pawn->CanMove(startPos, endPos, board);

	EXPECT_TRUE(canMove);
}

//upwards diagonally
TEST_F(PawnTest, ValidMove2) {
	Board board;

	Position startPos(3, 5);
	Position endPos(2, 6);
	bool canMove = pawn->CanMove(startPos, endPos, board);

	EXPECT_TRUE(canMove);
}

//moving backwards vertically
TEST_F(PawnTest, InvalidMove) {
	Board board;
	Position startPos(5, 4);
	Position endPos(6, 4);
	bool canMove = pawn->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}

//moving backwards diagonally
TEST_F(PawnTest, InvalidMove2) {
	Board board;
	Position startPos(5, 4);
	Position endPos(6, 6);
	bool canMove = pawn->CanMove(startPos, endPos, board);

	EXPECT_FALSE(canMove);
}