#pragma once

#include "Piece.h"

class Board;

class King: public Piece
{
public:
	King(EPieceColor color);
	bool CanMove(Position startPos, Position endPos, const Board& board);
	PositionList GetPossibleMoves(Position piecePos, const Board& board);
	bool CanMakeSmallCastling(EPieceColor color, const Board& board) const;
	bool CanMakeBigCastling(EPieceColor color, const Board& board) const;

private:
	bool VerifyKingMovmentCheck(Position startPos, Position endPos,  const Board& board) const;
};

