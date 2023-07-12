#include "King.h"

King::King(EPieceColor color) : Piece(EPieceType::King, color)
{
}

bool King::CanMove()
{
    return false;
}
