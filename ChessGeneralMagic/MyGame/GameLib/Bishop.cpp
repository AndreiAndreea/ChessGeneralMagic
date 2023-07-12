#include "Bishop.h"
#include "Board.h"


Bishop::Bishop(EPieceColor color) 
    : Piece (EPieceType::Bishop, color)
{

}

bool Bishop::CanMove(Position startPos, Position endPos, const Board& board)
{
    return false;
}