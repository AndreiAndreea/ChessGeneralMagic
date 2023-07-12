#include "Rook.h"

Rook::Rook(bool white) : Piece(white) { type = "R";}

Rook::Rook(EPieceColor color)
	: Piece(EPieceType::Rook, color)
{

}

bool Rook::CanMove(Position stratPos, Position endPos, Board board)
{

    return false;
}