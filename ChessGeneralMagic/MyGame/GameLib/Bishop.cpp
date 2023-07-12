#include "Bishop.h"

Bishop::Bishop(EPieceColor color) : Piece (EPieceType::Bishop, color)
{
}

bool Bishop::CanMove()
{
    return false;
}
