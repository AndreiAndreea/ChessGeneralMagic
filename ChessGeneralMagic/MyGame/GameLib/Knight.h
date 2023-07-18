#pragma once

#include "Piece.h"

class Board;

class Knight: public Piece
{
public:
	Knight(EPieceColor color);
	bool CanMove(Position startPos, Position endPos, const Board& board);
	void SetPossibleMoves(Position piecePos, const Board& board);

};