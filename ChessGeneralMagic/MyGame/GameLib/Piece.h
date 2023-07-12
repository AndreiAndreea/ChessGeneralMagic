#pragma once

#include "IPiece.h"

#include <string>
#include <memory>
using Position = std::pair<int, int>;

class Piece : public IPiece
{
public:
	Piece(EPieceType type, EPieceColor color);

	// IPiece implementation
	EPieceColor GetColor() const override;
	EPieceType GetType() const override;

	bool CanMove() override;

private:
	EPieceType m_type;
	EPieceColor m_color;
};

using PiecePtr = std::shared_ptr<Piece>;