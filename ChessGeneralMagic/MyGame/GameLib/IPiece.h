#pragma once

enum class EPieceColor
{
	Black,
	White
};

enum class EPieceType
{
	Rook,
	Bishop,
	Knight,
	King,
	Queen,
	Pawn
};

class IPiece
{
public:
	virtual EPieceColor GetColor() const = 0;
	virtual EPieceType GetType() const = 0;
	virtual bool CanMove(Position startPos, Position endPos, const Board& board) = 0;

	virtual ~IPiece() = default;
};