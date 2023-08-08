#pragma once

#include "IPieceInfo.h"
#include "EGameResult.h"
#include "Position.h"

class IGameListener
{
public:
	virtual void OnMoveMade(Position startPos, Position endPos, PositionList prevPossibleMoves) = 0;
	virtual void OnPawnUpgrade() = 0;
	virtual void OnGameOver(EGameResult result) = 0;
	virtual void OnCaptureMade(EPieceColor color, IPieceInfoPtrList capturedPieces) = 0;
	virtual void OnDraw() = 0;
	virtual void OnPawnUpgradePGN() = 0;

	virtual ~IGameListener() = default;
};

using IGameListenerWeakPtr = std::weak_ptr<IGameListener>;
using IGameListenerPtr = std::shared_ptr<IGameListener>;