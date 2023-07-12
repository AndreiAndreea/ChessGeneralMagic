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
	virtual bool CanMove() = 0;

	virtual ~IPiece() = default;
};