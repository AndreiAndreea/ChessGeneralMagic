#pragma once

#include "EGameState.h"
#include "Piece.h"

#include<memory>
#include<vector>

//using Position = std::pair<int, int>;
using PieceMatrix = std::vector<std::vector<PiecePtr>>;
using ConfigMatrix = std::vector<std::vector<char>>;
using ConfigMovesVesct = std::vector<std::vector<std::pair<Position, Position>>>;

class Board
{
public:
	Board();
	Board(int);
	Board(const Board& ob);
	Board(ConfigMatrix board);

	void InitializeBoard();

	PieceMatrix GetBoard() const;
	ConfigMovesVesct GetMovesVect() const;
	PositionList GetPossibleMoves(int i, int j) const;
	

	bool MakeMove(const Position& startPos, const Position& endPos);

	bool IsPieceColor(Position pos, EPieceColor color) const;

	void SetPiece(const Position& pos, EPieceColor color, EPieceType type);
	void SetPieceToNullptr(const Position& pos);

	void AddToMoves(Position startPos, Position endPos, EPieceColor color);

	//cant move piece if king is left in check
	bool IsKingLeftInCheck(const Position& startPos, const Position& endPos, EPieceColor pieceColor) const;
	bool IsKingInCheck(const Position& currentPos, EPieceColor color) const;
	bool IsCheckmate(EPieceColor color) const;
	bool IsStaleMate(EPieceColor color) const;

	bool IsThreefoldRepetitionDraw(EPieceColor color) const;

	std::vector<std::vector<bool>> GetCastlingVect() const;

private:
	void MoveRookForCastling(int castlingType, EPieceColor color);

private:
	PieceMatrix m_board;
	ConfigMovesVesct m_movesMade = { {}, {} };
	std::vector<std::vector<bool>> CastlingPossible = { {true, true}, {true, true} };
};