#include "Piece.h"

Piece::Piece(bool white)
{
	this->SetColor(white);
}


bool Piece::IsWhite()
{
	return this->white;
}

void Piece::SetColor(bool white)
{
	this->white = white;
}

void Piece::SetType(std::string type)
{
	this->type = type;
}

std::string Piece::GetType()
{
	return type;
}

EPieceType Piece::GetType() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Piece::CanMove()
{
	throw std::logic_error("The method or operation is not implemented.");
}

EPieceColor Piece::GetColor() const
{
	throw std::logic_error("The method or operation is not implemented.");
}
