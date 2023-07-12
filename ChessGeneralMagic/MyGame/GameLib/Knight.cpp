#include "Knight.h"
#include "Board.h"


Knight::Knight(EPieceColor color)
    :Piece(EPieceType::Knight,color)
{

}

bool Knight::CanMove(Position startPos, Position endPos, const Board& board)
{
    if (abs(startPos.first - endPos.first) == 2 && abs(startPos.second - endPos.second) == 1 || abs(startPos.first - endPos.first) == 1 && abs(startPos.second - endPos.second) == 2)
        return true;
    return false;
}

