#pragma once

#include "IGameStatus.h"
#include "IGameListener.h"
#include "EPieceType.h"
#include "EDrawComand.h"
#include "Position.h"

#include <memory>
#include <string>
#include <vector>
#include <utility>

using IGamePtr = std::shared_ptr<class IGame>;

using FullMove = std::pair<MoveStr, MoveStr>;
using FullMoveList = std::vector<FullMove>;

class IGame
{
public:
	static IGamePtr Produce();

	// subject methods
	virtual void AddListener(IGameListenerPtr listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;

	virtual void ResetGame() = 0;

	virtual ~IGame() = default;

	//Game Actions
	virtual void PlayerDrawComand(EDrawComand respons) = 0;
	virtual void MakeMove(Position startPos, Position endPos, bool isLoadingPGN = 0) = 0;
	virtual void UpgradePawnTo(EPieceType type) = 0;

	virtual void InitializeGameFEN(const std::string& strFEN) = 0;
	virtual void InitializeGamePGN(const std::string& movesPGN) = 0; 

	virtual void LoadFromPGNFile(const std::string& filePath) = 0;
	virtual void SaveToPGNFile(const std::string& filePath) = 0;

	//Game Status
	virtual const IGameStatus* GetStatus() const = 0;

	//virtual bool IsPlaying() const = 0;
	//virtual bool IsWaitingForPawnUpgrade() const = 0;
	//virtual bool IsDrawProposed() const = 0;
	//virtual bool IsDraw() const = 0;
	//virtual bool IsGameOver() const = 0;

	//virtual EPlayer GetWinner() const = 0;
	//virtual EPieceColor GetCurrentPlayer() const = 0;
	//virtual IPieceInfoPtrList GetCapturedPieces(EPieceColor color) const = 0;
	//virtual PositionList GetPossibleMoves(Position pos) const = 0;

	//virtual std::string GetPGN() const = 0;
	//virtual std::string GetFEN() const = 0;
	//
	//virtual MoveList GetMovesPGN(const std::string& pgnStr) const = 0;
	//virtual std::string GetPGNMovesSection() const = 0;

	//virtual IPieceInfoPtr GetPieceInfo(Position pos) const = 0;


};