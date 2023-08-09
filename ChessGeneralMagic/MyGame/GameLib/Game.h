#pragma once

#include "IGame.h"
#include "IChessTimerListener.h"
#include "Board.h"
#include "EGameState.h"
#include "EGameResult.h"
#include "PGNBuilder.h"
#include "ChessTimer.h"

using ConfigMatrix = std::vector<std::vector<char>>;
using ObserversList = std::vector<IGameListenerWeakPtr>;

class Game : public IGame, public IGameStatus, public IChessTimerListener
{
public:
	Game();
	Game(int turn, EGameState state, ConfigMatrix m);

	~Game();

	void InitializeGameFEN(const std::string& strFEN) override;
	void InitializeGamePGN(const std::string& movesPGN) override;

	void LoadFromPGNFile(const std::string& filePath) override;
	void SaveToPGNFile(const std::string& filePath) override;

	Board GetBoard() const;
	
	// IGame methods
	EPlayer GetWinner() const override;
	EPlayer GetCurrentPlayer() const override;
	PositionList GetPossibleMoves(Position pos) const override;
	IPieceInfoPtrList GetCapturedPieces(EPieceColor color) const override;
	IPieceInfoPtr GetPieceInfo(Position pos) const override;
	int GetTime(EPlayer player) const override;
	std::string GetFEN() const override;
	std::string GetPGN() const override;

	MoveList GetMovesPGN(const std::string& pgnStr) const override;
	std::string GetPGNMovesSection() const override;

	bool IsPlaying() const override;
	bool IsDrawProposed() const override;
	bool IsWaitingForPawnUpgrade() const override;
	bool IsDraw() const override;
	bool IsGameOver() const override;
	
	void PlayerDrawComand(EDrawComand respons) override;
	void MakeMove(Position startPos, Position endPos, bool isLoadingPGN = false) override;
	void UpgradePawnTo(EPieceType type) override;

	void ResetGame() override;

	// subject methods

	void AddListener(IGameListenerPtr listener) override;
	void RemoveListener(IGameListener* listener) override;

	void NotifyMoveMade(Position startPos, Position endPos, PositionList prevPossibleMoves);
	void NotifyCaptureMade(EPieceColor color, IPieceInfoPtrList capturedPieces);
	void NotifyPawnUpgrade();
	void NotifyGameOver(EGameResult result);
	void NotifyDraw();
	void NotifyPawnUpgradePGN();
	void NotifyUITimer();

	void OnTimerStart() override;

	Position FindPieceStartPos(int startRow, int startCol, Position endPos, EPieceType type, bool turn);
	std::tuple<Position, Position, EPieceType> ConvertPGNMoveToInfoMove(std::string move, bool turn);

	const IGameStatus* GetStatus() const override;

private:
	// to move in PGNBuilder?
	MoveStr GeneratePGNMove(Position startPos, Position endPos);
	void UpdatePGN(Position startPos, Position endPos);
	void UpdatePGNUpgradePawn(EPieceType type);
	void UpdatePGNDraw();
	void UpdatePGNMate(const Board& board);
	void UpdatePGNCheck(const Board& board);

	bool CanUpgradePawn(Position pos) const;
	bool IsState(EGameState state) const;
	void UpdateState(EGameState state);

private:
	Board m_board;
	int m_turn;
	int m_moves;
	MoveStr m_pgn;
	FullMoveList m_pgnMovesVect;
	EGameState m_state;
	ObserversList m_observers;
	ChessTimer m_timer;
	PGNBuilder m_pgnBuilder;
};