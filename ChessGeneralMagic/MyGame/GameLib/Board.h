#pragma once

#include "EGameState.h"
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
	std::vector<std::vector<std::pair<Position, Position>>> GetMovesVect() ;

	bool MakeMove(const Position& startPos, const Position& endPos);

	bool IsPieceColor(Position pos, EPieceColor color) const;

	void SetPiece(const Position& pos, EPieceColor color, EPieceType type);
	void SetPieceToNullptr(const Position& pos);

	void AddToMoves(Position startPos, Position endPos, EPieceColor color);

	//cant move piece if king is left in check
	bool IsKingLeftInCheck(const Position& startPos, const Position& endPos, EPieceColor pieceColor) const;

	//check if king is in check after opposite player move
	bool IsKingInCheck(const Position& currentPos, EPieceColor color) const;

	bool IsCheckmate(EPieceColor color) const;

	bool IsStaleMove(EPieceColor color) const;

	bool IsThreefoldRepetitionDraw(EPieceColor color) const;

	std::vector<std::vector<bool>> GetCastlingVect() const;

private:
	void MoveRookForCastling(int castlingType, EPieceColor color);

private:
	PieceMatrix m_board;
	std::vector<std::vector<std::pair<Position, Position>>> m_movesMade = { {}, {} };
	std::vector<std::vector<bool>> CastlingPossible = { {true, true}, {true, true} };
};