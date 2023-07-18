#include "Piece.h"

EPieceType Piece::GetType() const
{
	return m_type;
}

bool Piece::Is(EPieceType type, EPieceColor color) const
{
	return m_type == type && m_color == color;
}

bool Piece::IsOpposite(EPieceColor color, std::initializer_list<EPieceType> list) const
{
	if (m_color == color)
		return false;

	for (const auto& el : list)
		if (m_type == el)
			return true;

	return false;
}

PositionList Piece::GetPossibleMoves() const
{
	return m_possibleMoves;
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