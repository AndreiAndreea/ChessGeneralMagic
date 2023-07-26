#pragma once

#include "IGame.h"
#include "Board.h"
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

using ObserversList = std::vector<IGameListenerWeakPtr>;

class Game : public IGame
{
public:
	Game();

	Board GetBoard() const;
	
	// IGame methods
	EPlayer GetWinner() const override;
	EPieceColor GetCurrentPlayer() const override;
	PositionList GetPossibleMoves(Position pos) override;

	bool IsPlaying() const override;
	bool IsDrawProposed() const override;
	bool IsWaitingForPawnUpgrade() const override;
	bool IsDraw() const override;
	bool IsGameOver() const override;

	IPieceInfoPtr GetPieceInfo(Position pos) const override;
	
	void PlayerDrawComand(EDrawComand respons) override;
	void MakeMove(Position startPos, Position endPos) override;
	void UpgradePawnTo(EPieceType type) override;

	void ResetGame() override;

	// subject methods

	void AddListener(IGameListenerPtr listener) override;
	void RemoveListener(IGameListener* listener) override;

	void NotifyOnMoveMade();
	void NotifyOnPawnUpgrade();
	void NotifyOnGameOver();

private:
	bool CanUpgradePawn(Position pos) const;
	bool IsState(EGameState state) const;
	void UpdateState(EGameState state);

	static Position ConvertToPos(const std::string& pos);

private:
	Board m_board;
	int m_turn;
	EGameState m_state;
	ObserversList m_observers;
};