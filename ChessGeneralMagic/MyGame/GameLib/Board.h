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
	Board(BoardType board);
	void InitializeBoard();
	bool MakeMove(Position startPos, Position endPos);
	BoardType GetBoard() const;
	//void printBoard();

private:
	//bool IsKingIn

private:
	BoardType m_board;
};