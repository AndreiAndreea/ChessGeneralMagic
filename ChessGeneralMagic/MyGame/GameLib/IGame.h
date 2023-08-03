#pragma once

#include "IGameListener.h"
#include "IPieceInfo.h"
#include "EPieceColor.h"
#include "EPieceType.h"
#include "EDrawComand.h"
#include "PositionList.h"

#include <memory>
#include <string>
#include <vector>
#include <utility>

enum class EPlayer
{
	White,
	Black,
	None
};

//class IPieceInfo
//{
//public:
//	virtual EPieceColor GetColor() const = 0;
//	virtual EPieceType GetType() const = 0;
//
//	virtual ~IPieceInfo() = default;
//};

//using IPieceInfoPtr = std::shared_ptr<IPieceInfo>;

using IGamePtr = std::shared_ptr<class IGame>;

using IGameListenerWeakPtr = std::weak_ptr<IGameListener>;
using IGameListenerPtr = std::shared_ptr<IGameListener>;
using ConfigFEN = std::string;
using ConfigPGN = std::string;
using MovesPGN = std::vector<std::pair<ConfigPGN, ConfigPGN>>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual EPlayer GetWinner() const = 0;
	virtual EPieceColor GetCurrentPlayer() const = 0;
	virtual IPieceInfoPtrList GetCapturedPieces(EPieceColor color) const = 0;
	virtual PositionList GetPossibleMoves(Position pos) = 0;
	virtual ConfigFEN GenerateFEN() = 0;
	virtual ConfigPGN GetPGN() const = 0;
	virtual MovesPGN GetMovesPGN() const = 0;

	virtual void InitializeGameFEN(ConfigFEN strFEN) = 0;
	virtual void InitializeGamePGN(std::vector<ConfigPGN> movesPGN) = 0;

	virtual bool IsPlaying() const = 0;
	virtual bool IsWaitingForPawnUpgrade() const = 0;
	virtual bool IsDrawProposed() const = 0;
	virtual bool IsDraw() const = 0;
	virtual bool IsGameOver() const = 0;

	virtual void PlayerDrawComand(EDrawComand respons) = 0;
	virtual void MakeMove(Position startPos, Position endPos, bool isLoadingPGN) = 0;
	virtual void UpgradePawnTo(EPieceType type) = 0;

	virtual void ResetGame() = 0;

	virtual IPieceInfoPtr GetPieceInfo(Position pos) const = 0;

	virtual std::vector<std::string> parsePGNChessString(const std::string& pgnString) =0;

	// subject methods
	virtual void AddListener(IGameListenerPtr listener) = 0;
	virtual void RemoveListener(IGameListener* listener) = 0;

	virtual ~IGame() = default;
};