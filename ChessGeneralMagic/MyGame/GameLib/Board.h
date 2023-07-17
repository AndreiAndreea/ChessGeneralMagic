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
using PieceMatrix = std::vector<std::vector<PiecePtr>>;
using ConfigMatrix = std::vector<std::pair<PiecePtr, Position>>;

class Board
{
public:
	Board();
	Board( ConfigMatrix piecePos);

	void InitializeBoard();

	PieceMatrix GetBoard() const;

	void MakeMove(Position startPos, Position endPos);

	//private
	void SetPiece(Position pos, EPieceColor color, EPieceType type);
	void SetPieceToNullptr(Position pos);

	//cant move piece if king is left in check

	bool IsKingInCheck(Position startPos, Position endPos, EPieceColor pieceColor) const;
	//checking if it is checkmate
	//bool IsCheckmate() const;

private:
	PieceMatrix m_board;
};