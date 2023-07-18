#pragma once

#include "IGame.h"
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
	void Play() override;
	
	EPlayer GetWinner() const override;
	bool IsGameOver() const override;

	IPieceInfoPtr GetPieceInfo(int i, int j) const override;
	
	bool MakeMove(std::string startPosStr, std::string endPosStr) override;

private:
	Position ConvertToPos(std::string pos);
	bool IsInputValid(Position startPos, Position endPos);

private:
	Board m_board;
	int m_turn;
	//Player m_whitePlayer, m_blackPlayer;
};