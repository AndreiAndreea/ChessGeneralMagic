#include "gtest/gtest.h"

#include "Board.h"

TEST(BoardTest, ThreefoldRep)
{
	ConfigMatrix m = {
		{'-', 'R', '-', '-', '-', '-', '-', '-'},
		{'-', '-', 'b', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', 'n', '-', '-', '-'},
		{'-', '-', '-', 'r', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', 'B', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-'}
	};

	Board board(m);

	//move
	board.MakeMove({ 6, 2 }, { 5, 3 }); // Move black bishop
	board.MakeMove({ 3, 4 }, { 1, 5 }); // Move white knight

	//move back
	board.MakeMove({ 5, 3 }, { 6, 2 }); // Move black bishop back to the initial position 
	board.MakeMove({ 1, 5 }, { 3, 4 }); // Move white knight back to the initial position 

	//move
	board.MakeMove({ 6, 2 }, { 5, 1 }); // Move black bishop again 
	board.MakeMove({ 3, 4 }, { 1, 5 }); // Move white knight
	
	//move back
	board.MakeMove({ 5, 3 }, { 6, 2 }); // Move black bishop back to the initial position 
	board.MakeMove({ 1, 5 }, { 3, 4 }); // Move white knight back to the initial position 


	EXPECT_TRUE(board.IsThreefoldRepetitionDraw());
}