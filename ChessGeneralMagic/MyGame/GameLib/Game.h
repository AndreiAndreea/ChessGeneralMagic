#pragma once

#include<iostream>

#include "Board.h"
#include "Player.h"
#include "IGame.h"

class Game : public IGame
{
public:
	Game();
	Board GetBoard();
	void Play() override;
	EPlayer GetWinner() const override;
	bool IsGameOver() const override;
	void MakeMove(Position startPos, Position endPos, Board& board);


private:
	Board m_board;
	Player m_whitePlayer, m_blackPlayer;
};