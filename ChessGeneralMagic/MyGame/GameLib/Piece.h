#pragma once

#include "IPiece.h"

#include <string>
#include <memory>

class Piece : public IPiece
{
protected:
	bool white = false;
	std::string type;
public:
	Piece();
	Piece(bool white);
	bool IsWhite();
	void SetColor(bool white);
	void SetType(std::string type);
	std::string GetType(); 
	void SetPiece();
};

using PiecePtr = std::shared_ptr<Piece>;