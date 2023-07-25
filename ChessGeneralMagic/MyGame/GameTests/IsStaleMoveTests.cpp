#include "gtest/gtest.h"

#include "Board.h"

TEST(BoardTest, StaleMove)
{
		ConfigMatrix m = { 
	{'-', '-', '-', '-', 'K', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', 'R', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', '-'},
	{'-', '-', '-', '-', 'Q', '-', '-', '-'},
	{'-', '-', '-', '-', '-', '-', '-', 'k'}
	};

	Board board(m);
	EXPECT_TRUE(board.IsStaleMate(EPieceColor::White));
}

TEST(BoardTest, StaleMove2)
{
	ConfigMatrix m = {
{'-', '-', '-', '-', 'K', '-', '-', '-'},
{'-', '-', '-', '-', '-', '-', '-', '-'},
{'-', '-', '-', '-', '-', '-', '-', '-'},
{'-', '-', '-', '-', '-', '-', 'R', '-'},
{'-', 'b', '-', '-', '-', '-', '-', '-'},
{'-', '-', '-', '-', '-', '-', '-', '-'},
{'-', '-', '-', '-', 'Q', '-', '-', '-'},
{'-', '-', '-', '-', '-', '-', '-', 'k'}
	};

	Board board(m);
	EXPECT_FALSE(board.IsStaleMate(EPieceColor::White));
}