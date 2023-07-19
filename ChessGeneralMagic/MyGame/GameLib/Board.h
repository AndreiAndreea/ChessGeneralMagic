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
	Board(int);
	Board( ConfigMatrix piecePos);

	void InitializeBoard();

	PieceMatrix GetBoard() const;

	bool MakeMove(Position startPos, Position endPos);

	//private
	void SetPiece(Position pos, EPieceColor color, EPieceType type);
	void SetPieceToNullptr(Position pos);

	//cant move piece if king is left in check
	bool IsKingLeftInCheck(Position startPos, Position endPos, EPieceColor pieceColor) const;
	//check if king is in check after opposite player move
	bool IsKingInCheck(Position currentPos, EPieceColor color) const;
	//checking if it is checkmate
	bool IsCheckmate(EPieceColor color) const;



private:
	PieceMatrix m_board;
};