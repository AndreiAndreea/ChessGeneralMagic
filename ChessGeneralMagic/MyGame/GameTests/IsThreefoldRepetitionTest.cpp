#include "gtest/gtest.h"

#include "Game.h"

TEST(BoardTest, ThreefoldRep)
{
	ConfigMatrix m = {
		{'-', 'K', '-', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', 'b', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', 'n', '-', '-', '-'},
		{'-', '-', '-', 'k', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-'},
		{'-', '-', 'B', '-', '-', '-', '-', '-'},
		{'-', '-', '-', '-', '-', '-', '-', '-'}
	};

	//Board board(m);

	Game g(1, EGameState::Playing, m);

	//move
	g.MakeMove({ 6, 2 }, { 5, 3 }); // Move black bishop
	g.MakeMove({ 3, 4 }, { 1, 5 }); // Move white knight

	//move back
	g.MakeMove({ 5, 3 }, { 6, 2 }); // Move black bishop back to the initial position 
	g.MakeMove({ 1, 5 }, { 3, 4 }); // Move white knight back to the initial position 

	//move
	g.MakeMove({ 6, 2 }, { 5, 1 }); // Move black bishop again 
	g.MakeMove({ 3, 4 }, { 1, 5 }); // Move white knight
	
	//move back
	g.MakeMove({ 5, 1 }, { 6, 2 }); // Move black bishop back to the initial position 
	g.MakeMove({ 1, 5 }, { 3, 4 }); // Move white knight back to the initial position 

	EXPECT_TRUE(g.GetBoard().IsThreefoldRepetitionDraw());
}