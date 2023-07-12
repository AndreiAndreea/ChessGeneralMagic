#pragma once

#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"

#include<memory>

//using Position = std::pair<int, int>;

class Board
{
public:
	Board();
	void InitializeBoard();
	bool MakeMove(Position startPos, Position endPos, Board& board);
	void printBoard();

private:
	PiecePtr m_board[10][10];
};