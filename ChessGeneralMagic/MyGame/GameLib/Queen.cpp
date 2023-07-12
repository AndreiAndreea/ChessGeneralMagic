#include "Queen.h"


Queen::Queen(EPieceColor color) 
    :Piece(EPieceType::Queen,color)
{

}

bool Queen::CanMove()
{
    return false;
}
