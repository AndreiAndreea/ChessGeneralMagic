#pragma once
#include<iostream>
#include "Board.h"
#include "Player.h"
#include "IGame.h"

class Game : public IGame
{

public:

	void Play() override;
	EPlayer getWinner() override;
	bool isGameOver() override;

};