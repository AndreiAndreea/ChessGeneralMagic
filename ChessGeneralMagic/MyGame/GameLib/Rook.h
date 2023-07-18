#pragma once

#include "Piece.h"

class Board;

class Rook : public Piece
{
public:
	Rook(EPieceColor color);
	bool CanMove(Position stratPos, Position endPos, const Board& board);
	void SetPossibleMoves(Position piecePos, const Board& board);
};