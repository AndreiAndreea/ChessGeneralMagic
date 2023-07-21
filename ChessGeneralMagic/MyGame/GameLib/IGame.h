#pragma once

#include "EPieceColor.h"
#include "EPieceType.h"

#include "OutOfBoundException.h"
#include "InvalidMovingPatternException.h"
#include "InvalidStartPositionExcepton.h"
#include "KingLeftInCheckException.h"
#include "NotStateDrawProposedException.h"
#include "NotStatePlayingException.h"
#include "NotStateWaitingForPawnUpdate.h"
#include "InvalidUpgradeType.h"
#include "InvalidDrawResponseException.h"

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

class IPieceInfo
{
public:
	virtual EPieceColor GetColor() const = 0;
	virtual EPieceType GetType() const = 0;

	virtual ~IPieceInfo() = default;
};

using Position = std::pair<int, int>;
using IPieceInfoPtr = std::shared_ptr<IPieceInfo>;
using IGamePtr = std::shared_ptr<class IGame>;

class IGame
{
public:
	static IGamePtr Produce();

	virtual EPlayer GetWinner() const = 0;
	virtual EPlayer GetCurrentPlayer() const = 0;
	virtual std::vector<Position> GetPossibleMoves(int i, int j) = 0;

	virtual bool IsStatePlaying() const = 0;
	virtual bool IsStateWaitingForPawnUpgrade() const = 0;
	virtual bool IsStateDrawProposed() const = 0;
	virtual bool IsStateDraw() const = 0;
	virtual bool IsGameOver() const = 0;

	virtual void PlayerComand(const std::string& comand) = 0;

	virtual void DrawReaponse(const std::string& respons) = 0;
	virtual void UpgradePawnTo(const std::string& type) = 0;
	virtual void MakeMove(Position startPos, Position endPos) = 0;

	virtual IPieceInfoPtr GetPieceInfo(int i, int j) const = 0;

	virtual ~IGame() = default;
};