#pragma once

#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"

#include<memory>
#include<vector>

//using Position = std::pair<int, int>;
using BoardType = std::vector<std::vector<PiecePtr>>;

class Board
{
public:
	Board();
	void InitializeBoard();
	bool MakeMove(Position startPos, Position endPos);
	BoardType GetBoard() const;
	//void printBoard();

private:
	BoardType m_board;
};