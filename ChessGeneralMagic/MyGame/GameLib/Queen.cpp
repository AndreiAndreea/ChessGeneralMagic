#include "Queen.h"

Queen::Queen(bool white) : Piece(white) { type = "Q"; }

bool Queen::CanMove()
{
    return false;
}
