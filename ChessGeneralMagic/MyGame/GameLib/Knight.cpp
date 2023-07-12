#include "Knight.h"

Knight::Knight(EPieceColor color)
    :Piece(EPieceType::Knight,color)
{

}

bool Knight::CanMove()
{
    return false;
}

