#pragma once

#include "EGameState.h"
#include "Piece.h"

#include<memory>
#include <bitset>

//using Position = std::pair<int, int>;
using PieceMatrix = std::vector<std::vector<PiecePtr>>;
using ConfigMatrix = std::vector<std::vector<char>>;
using ConfigCastlingPossible = std::vector<std::vector<bool>>;

using BoardConfig = std::bitset<256>;
using BoardConfigList = std::vector<BoardConfig>;

class Board
{
public:
	Board();
	Board(int);
	Board(const Board& ob);
	Board(ConfigMatrix board);

	void InitializeBoard();

	PieceMatrix GetBoard() const;
	PositionList GetPossibleMoves(Position pos) const;


	bool MakeMove(const Position& startPos, const Position& endPos);

	bool IsPieceColor(Position pos, EPieceColor color) const;

	void SetPiece(const Position& pos, EPieceColor color, EPieceType type);
	void SetPieceToNullptr(const Position& pos);

	//cant move piece if king is left in check
	bool IsKingLeftInCheck(const Position& startPos, const Position& endPos, EPieceColor pieceColor) const;
	bool IsKingInCheck(const Position& currentPos, EPieceColor color) const;
	bool IsCheckmate(EPieceColor color) const;
	bool IsStaleMate(EPieceColor color) const;
	bool IsInsufficientMaterial() const;
	bool IsThreefoldRepetitionDraw();
	
	bool IsUpgradeablePawn(Position pos) const;

	void SetBitBoardsToEmpty();

	ConfigCastlingPossible GetCastlingVect() const;

private:
	void MoveRookForCastling(int castlingType, EPieceColor color);
	BoardConfig GenerateBitset();

private:
	PieceMatrix m_board;
	ConfigCastlingPossible CastlingPossible = { {true, true}, {true, true} };

	BoardConfigList m_bitBoards;
};