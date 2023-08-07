#pragma once

#include "IGame.h"
#include "Board.h"
#include "EGameState.h"
#include "EGameResult.h"
#include "PGNBuilder.h"

using ConfigMatrix = std::vector<std::vector<char>>;
using ObserversList = std::vector<IGameListenerWeakPtr>;

class Game : public IGame
{
public:
	Game();
	Game(int turn, EGameState state, ConfigMatrix m);

	void InitializeGameFEN(ConfigFEN strFEN) override;
	void InitializeGamePGN(std::vector<std::string> movesPGN) override;

	void LoadPGNFromFile(const std::string& filePath) override;
	void SavePGNToFile(const std::string& filePath) override;

	Board GetBoard() const;
	
	// IGame methods
	EPlayer GetWinner() const override;
	EPieceColor GetCurrentPlayer() const override;
	PositionList GetPossibleMoves(Position pos) override;
	IPieceInfoPtrList GetCapturedPieces(EPieceColor color) const override;
	IPieceInfoPtr GetPieceInfo(Position pos) const override;
	ConfigPGN GetPGN() const override;
	ConfigFEN GenerateFEN() override;

	void SetPGNString(const ConfigPGN strPGN) override;

	std::vector<ConfigPGN> GetMovesPGN() const override;

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

	Position FindPieceStartPos(int startRow, int startCol, Position endPos, EPieceType type, bool turn);
	std::tuple<Position, Position, EPieceType> ConvertPGNMoveToInfoMove(std::string move, bool turn);



private:
	// to move in PGNBuilder?
	ConfigPGN GeneratePGNMove(Position startPos, Position endPos);
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
	ConfigPGN m_pgn;
	MovesPGN m_pgnMovesVect;
	EGameState m_state;
	ObserversList m_observers;

	PGNBuilder m_pgnBuilder;
};