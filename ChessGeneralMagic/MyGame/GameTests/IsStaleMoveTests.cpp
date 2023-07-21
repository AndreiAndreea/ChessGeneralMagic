#include "gtest/gtest.h"

#include "Board.h"

TEST(BoardTest, StaleMove)
{
	ConfigMatrix initializedBoard = {
		{"Rb", "Nb", "Bb", "Qb", "Kb", "Bb", "Nb", "Rb"},
		{'Pb', 'Pb', 'Pb', 'Pb', 'Pb', 'Pb', 'Pb', 'Pb'},
		{0,   0,   0,   0,   0,   0,   0,   0},
		{0,   0,   0,   0,   0,   0,   0,   0},
		{0,   0,   0,   0,   0,   0,   0,   0},
		{0,   0,   0,   0,   0,   0,   0,   0},
		{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
		{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
	};

	Board board();
}