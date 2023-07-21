#pragma once

#include "IGame.h"
#include "Board.h"
#include "Player.h"
#include "EGameState.h"


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

	bool PlayerComand(const std::string& comand) override;
	
	bool IsStateDrawProposed() const override;
	bool IsStateWaitingForPawnUpgrade() const override;
	bool IsStateDraw() const override;
	bool IsGameOver() const override;

	IPieceInfoPtr GetPieceInfo(int i, int j) const override;
	
	bool DrawReaponse(const std::string& respons) override;
	bool UpgradePawnTo(const std::string& type) override;
	bool MakeMove(Position startPos, Position endPos) override;


private:
	bool CanUpgradePawn(Position pos) const;
	bool IsState(EGameState state) const;
	void UpdateState(EGameState state);

	static Position ConvertToPos(const std::string& pos);

private:
	Board m_board;
	int m_turn;
	EGameState m_state;
};