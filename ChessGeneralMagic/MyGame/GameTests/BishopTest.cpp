#include "gtest/gtest.h"

#include "Bishop.h"
#include "Board.h"

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
	std::vector<std::pair<Position, Position>> possibleMoves= { {Position(2,2), Position(5,5)}, {Position(4,3), Position(6,5)} };

	for(auto it: possibleMoves)
	EXPECT_TRUE(bishop->CanMove(it.first, it.second, board));
}

TEST_F(BishopTest, InvalidMove) {
	Board board;
	std::vector<std::pair<Position, Position>> possibleMoves = { {Position(4,4), Position(2,6)}, {Position(2,2), Position(4,5)} };

	for (auto it : possibleMoves)
	EXPECT_FALSE(bishop->CanMove(it.first, it.second, board));
}