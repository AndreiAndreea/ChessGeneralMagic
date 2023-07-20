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
	Board(const Board& ob);
	Board(ConfigMatrix piecePos);

	void InitializeBoard();

	PieceMatrix GetBoard() const;

	bool MakeMove(const Position& startPos, const Position& endPos);

	bool IsPieceColor(Position pos, EPieceColor color) const;

	void SetPiece(const Position& pos, EPieceColor color, EPieceType type);
	void SetPieceToNullptr(const Position& pos);

	//IPieceInfoPtr GetPieceInfo() const;

	//cant move piece if king is left in check
	bool IsKingLeftInCheck(const Position& startPos, const Position& endPos, EPieceColor pieceColor) const;

	//check if king is in check after opposite player move
	bool IsKingInCheck(const Position& currentPos, EPieceColor color) const;

	//checking if it is checkmate
	bool IsCheckmate(EPieceColor color) const;

	std::vector<std::vector<bool>> GetCastlingVect() const;

private:
	void MoveRookForCastling(int castlingType, EPieceColor color);

private:
	PieceMatrix m_board;
	std::vector<std::vector<bool>> CastlingPossible = { {true, true}, {true, true} };
};