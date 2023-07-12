#include "Knight.h"

Knight::Knight(bool white) : Piece(white) { type = "Kn"; }

bool Knight::CanMove()
{
    return false;
}
