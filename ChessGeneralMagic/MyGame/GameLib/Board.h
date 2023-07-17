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
	BoardType GetBoard() const;
	void SetPiece(Position pos, EPieceColor color, EPieceType type);
	void SetPieceToNullptr(Position pos);

	void PrintBoard();
	//cant move piece if king is left in check
	bool IsKingInCheck(Position startPos, Position endPos, EPieceColor pieceColor) const;
	//checking if it is checkmate
	//bool IsCheckmate() const;

private:
	BoardType m_board;
};