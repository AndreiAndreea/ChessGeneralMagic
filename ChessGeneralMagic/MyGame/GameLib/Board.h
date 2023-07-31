#pragma once

#include "Piece.h"
#include "IPieceInfo.h"
#include "EGameState.h"

#include<memory>
#include <bitset>

//using Position = std::pair<int, int>;
using PieceMatrix = std::vector<std::vector<PiecePtr>>;
using ConfigMatrix = std::vector<std::vector<char>>;
using ConfigCastlingPossible = std::vector<std::vector<bool>>;
using ConfigCapturedPieces = std::vector<IPieceInfoPtrList>;
using BoardConfig = std::bitset<256>;
using BoardConfigList = std::vector<BoardConfig>;
using ConfigFEN = std::string;

class Board
{
public:
	Board();
	Board(int);
	Board(const Board& ob);
	Board(ConfigMatrix board);

	void InitializeBoardFEN(ConfigFEN& strFEN);
	void InitializeBoard();

	PieceMatrix GetBoard() const;
	PositionList GetPossibleMoves(Position pos) const;
	IPieceInfoPtrList GetCapturedPieces(EPieceColor color) const;
	IPieceInfoPtr GetPieceInfo(Position pos) const;
	ConfigFEN GenerateBoardFEN();
	ConfigFEN GenerateCastlingPossibleFEN();

	bool MakeMove(const Position& startPos, const Position& endPos);

	bool IsPieceColor(Position pos, EPieceColor color) const;

	void SetPiece(const Position& pos, EPieceColor color, EPieceType type);
	void SetPieceToNullptr(const Position& pos);
	void SetBitBoardsToEmpty();

	void AddCapturedPiece(IPieceInfoPtr piece);
	void RemoveLastCapturedPiece(EPieceColor color);

	//cant move piece if king is left in check
	bool IsKingLeftInCheck(const Position& startPos, const Position& endPos, EPieceColor pieceColor) const;
	bool IsKingInCheck(const Position& currentPos, EPieceColor color) const;
	bool IsCheckmate(EPieceColor color) const;
	bool IsStaleMate(EPieceColor color) const;
	bool IsInsufficientMaterial() const;
	bool IsThreefoldRepetitionDraw();
	
	bool IsUpgradeablePawn(Position pos) const;


	ConfigCastlingPossible GetCastlingVect() const;

private:
	void MoveRookForCastling(int castlingType, EPieceColor color);
	BoardConfig GenerateBitset();

private:
	PieceMatrix m_pieceMatrix;
	ConfigCastlingPossible m_castlingPossible = { {true, true}, {true, true} };
	ConfigCapturedPieces m_capturedPieces = { {}, {} };
	BoardConfigList m_bitBoards;
};