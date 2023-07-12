#include "King.h"
#include "Board.h"


King::King(EPieceColor color) 
    : Piece(EPieceType::King, color)
{

}

bool King::CanMove(Position startPos, Position endPos, const Board& board)
{
    return false;
}
