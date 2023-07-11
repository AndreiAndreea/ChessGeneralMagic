#pragma once

#include "Piece.h"

#include<memory>

using Position = std::pair<int, int>;

class Board
{
public:
	Board();
	void InitializeBoard();
	bool MakeMove(Position startPos, Position endPos, Board& board);

private:
	PiecePtr m_board[8][8];
};