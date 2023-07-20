#pragma once

#include "IGame.h"
#include "EGameState.h"
#include "Board.h"
#include "Player.h"


class PieceInfo : public IPieceInfo
{
public:
	PieceInfo(EPieceType type, EPieceColor color);

	EPieceColor GetColor() const override;
	EPieceType GetType() const override;

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
	EPlayer GetWinner() const override;
	EPlayer GetCurrentPlayer() const override;
	
	bool IsGameOver() const override;
	bool IsDraw() const override;

	IPieceInfoPtr GetPieceInfo(int i, int j) const override;
	
	bool MakeMove(const std::string& comand) override;

private:
	static Position ConvertToPos(const std::string& pos);

private:
	Board m_board;
	int m_turn;
	EGameState state;
	bool m_proposeDraw, m_draw;
};