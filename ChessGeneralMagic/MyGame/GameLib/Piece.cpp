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

void Piece::SetType(char type)
{
	this->type = type;
}

char Piece::GetType()
{
	return type;
}
