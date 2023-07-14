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
	Board(std::vector<std::pair<PiecePtr, Position>> piecePos);

	void InitializeBoard();
	bool MakeMove(Position startPos, Position endPos);
	BoardType GetBoard() const;
	void SetPiece(Position startPos, EPieceColor color, EPieceType type);

	//void printBoard();
	bool IsKingInCheck(Position startPos, Position endPos, EPieceColor pieceColor) const;

//private:
//	bool VerifyKingMovmentCheck(Position startPos, Position endPos);

private:
	BoardType m_board;
};