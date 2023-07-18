#pragma once

#include "Piece.h"

class Board;

class Knight: public Piece
{
public:
	Knight(EPieceColor color);
	bool CanMove(Position startPos, Position endPos, const Board& board);
	PositionList GetPossibleMoves(Position piecePos, const Board& board);

};