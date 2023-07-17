#pragma once

#include "IPiece.h"

#include <string>
#include <memory>
#include <cmath>

class Board;

class Piece : public IPiece
{
public:
	Piece(EPieceType type, EPieceColor color);

	// IPiece implementation
	EPieceColor GetColor() const override;
	EPieceType GetType() const override;

	bool Is(EPieceType type, EPieceColor color) const override;
	bool IsOpposite(EPieceColor color, std::initializer_list<EPieceType> list) const;

private:
	EPieceType m_type;
	EPieceColor m_color;
	std::vector<Position> m_possibleMoves;
};

using PiecePtr = std::shared_ptr<Piece>;