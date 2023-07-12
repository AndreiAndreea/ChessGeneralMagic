#include "Piece.h"


EPieceType Piece::GetType() const
{
	return m_type;
}

bool Piece::CanMove()
{
	return true;
}

Piece::Piece(EPieceType type, EPieceColor color)
{
	m_type = type;
	m_color = color;
}

EPieceColor Piece::GetColor() const
{
	return m_color;
}
