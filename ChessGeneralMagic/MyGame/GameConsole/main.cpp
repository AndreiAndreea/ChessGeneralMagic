#include<iostream>

#include "IGame.h"
#include "Board.h"
#include "Game.h"

int main()
{
	Board board;
	Game game;
	board.InitializeBoard();
	board.PrintBoard();
	auto game2 = game.GetBoard();
	game.MakeMove(Position(2, 2), Position(3, 2), game2);
	std::cout << "\n\n\n";
	game2.PrintBoard();
	return 0;
}