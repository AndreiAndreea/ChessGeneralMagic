#pragma once

#include "IGame.h"
#include "Board.h"
#include "Player.h"

class PieceInfo : public IPieceInfo
{
public:
	PieceInfo(EPieceType type, EPieceColor color);

	EPieceColor GetColor() override;
	EPieceType GetType() override;

private:
	EPieceType m_type;
	EPieceColor m_color;
};

class Game : public IGame
{
public:
	Game();

	Board GetBoard() const;
	
	// IGame methods
	void Play() override;
	
	EPlayer GetWinner() const override;
	bool IsGameOver() const override;

	IPieceInfoPtr GetPieceInfo(int i, int j) override;
	
	void MakeMove(Position startPos, Position endPos) override;

private:
	Board m_board;
	//Player m_whitePlayer, m_blackPlayer;
};