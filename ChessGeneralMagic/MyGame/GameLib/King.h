#pragma once

#include "Piece.h"

class Board;

class King: public Piece
{
public:
	King(EPieceColor color);
	bool CanMove(Position startPos, Position endPos, const Board& board);
	
private:
	bool VerifyKingMovmentCheck(Position startPos, Position endPos,  Board board);
};

