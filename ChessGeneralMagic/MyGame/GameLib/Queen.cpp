#include "Queen.h"
#include "Board.h"


Queen::Queen(EPieceColor color) 
    : Piece(EPieceType::Queen,color)
{

}

bool Queen::CanMove(Position startPos, Position endPos, const Board& board)
{
    return false;
}
