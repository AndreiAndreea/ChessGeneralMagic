#include "Knight.h"
#include "Board.h"


Knight::Knight(EPieceColor color)
    :Piece(EPieceType::Knight,color)
{

}

bool Knight::CanMove(Position startPos, Position endPos, const Board& board)
{
    return false;
}

