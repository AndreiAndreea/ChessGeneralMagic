#pragma once

#include "IPiece.h"

#include <memory>

class Piece : public IPiece
{
protected:
	bool white = false;
	char type;
public:
	Piece(bool white);
	bool IsWhite();
	void SetColor(bool white);
	void SetType(char type);
	char GetType(); 
};

using PiecePtr = std::shared_ptr<Piece>;