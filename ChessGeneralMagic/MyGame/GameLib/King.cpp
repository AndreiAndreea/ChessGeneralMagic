#include "King.h"

King::King(bool white) : Piece(white) { type = "Kg"; }

bool King::CanMove()
{
    return false;
}
