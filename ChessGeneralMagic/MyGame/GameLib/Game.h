#pragma once

#include "IGame.h"
#include "IGameListener.h"
#include "Board.h"
#include "EGameState.h"
#include "PositionList.h"

using IGameListenerWeakPtr = std::weak_ptr<IGameListener>;
using IGameListenerPtr = std::shared_ptr<IGameListener>;

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
	EPieceColor GetCurrentPlayer() const override;
	PositionList GetPossibleMoves(int i, int j) override;

	void PlayerComand(const std::string& comand) override;
	
	bool IsStatePlaying() const override;
	bool IsStateDrawProposed() const override;
	bool IsStateWaitingForPawnUpgrade() const override;
	bool IsStateDraw() const override;
	bool IsGameOver() const override;

	IPieceInfoPtr GetPieceInfo(int i, int j) const override;
	
	void DrawReaponse(const std::string& respons) override;
	void UpgradePawnTo(const std::string& type) override;
	void MakeMove(Position startPos, Position endPos) override;

	void ResetGame() override;

	void NotifyAll();
	void AddListener(IGameListenerPtr listener);
	void RemoveListener(IGameListenerPtr listener);

private:
	bool CanUpgradePawn(Position pos) const;
	bool IsState(EGameState state) const;
	void UpdateState(EGameState state);

	static Position ConvertToPos(const std::string& pos);

private:
	Board m_board;
	int m_turn;
	EGameState m_state;
	std::vector<IGameListenerWeakPtr> m_observers;
};