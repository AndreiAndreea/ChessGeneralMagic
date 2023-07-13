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
	std::vector<std::pair<Position, Position>> possibleMoves = { {Position(4,4), Position(3,4)}, {Position(4,4), Position(5,3)} };

	for(auto it:possibleMoves)
	EXPECT_TRUE(king->CanMove(it.first, it.second, board));
}


TEST_F(KingTest, InvalidMove) {
	Board board;
	std::vector<std::pair<Position, Position>> possibleMoves = { {Position(4,4), Position(2,5)}, {Position(4,4), Position(6,6)},{Position(1,4), Position(1,6)} };

	for(auto it:possibleMoves)
	EXPECT_FALSE(king->CanMove(it.first,it.second, board));
}
