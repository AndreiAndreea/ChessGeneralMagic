#pragma once

#include<iostream>

#include "Board.h"
#include "Player.h"
#include "IGame.h"

class Game : public IGame
{
public:
	void Play() override;
	EPlayer GetWinner() const override;
	bool IsGameOver() const override;

private:
	Board m_board;
	Player m_whitePlayer, m_blackPlayer;
};