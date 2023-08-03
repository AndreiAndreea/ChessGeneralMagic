#include "gtest/gtest.h"

#include "Game.h"

TEST(FEN, Test1)
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
	
	Game g(0, EGameState::Playing, m);
	
	auto str = g.GenerateFEN();
	std::string strFEN = "1k6/8/2B5/4N3/3K4/8/2b5/8 w QKqk";
	EXPECT_EQ(g.GenerateFEN(), strFEN);
}

TEST(FEN, Test2)
{

	ConfigMatrix m  = {
        {'r', 'n', '-', 'k', '-', '-', '-', 'r'},
        {'p', 'p', 'p', '-', 'p', 'p', 'p', 'p'},
        {'-', '-', '-', 'p', '-', '-', '-', '-'},
        {'-', '-', 'b', '-', 'b', 'n', '-', '-'},
        {'q', '-', 'P', '-', 'P', '-', 'P', 'N'},
        {'R', '-', '-', '-', '-', 'K', '-', '-'},
        {'P', '-', 'P', '-', 'P', 'P', 'P', '-'},
        {'-', '-', 'B', 'Q', '-', 'B', 'N', 'R'}
    };
	

	Game g(0, EGameState::Playing, m);

	auto str = g.GenerateFEN();
	std::string strFEN = "RN1K3R/PPP1PPPP/3P4/2B1BN2/Q1p1p1pn/r4k2/p1p1ppp1/2bq1bnr w QKqk";
	EXPECT_EQ(g.GenerateFEN(), strFEN);
}