#include "Queen.h"
#include "Board.h"

Queen::Queen(EPieceColor color) 
    : Piece(EPieceType::Queen,color)
{

}

bool Queen::CanMove(Position startPos, Position endPos, const Board& board)
{
    Bishop bishop(EPieceColor::Black);
    Rook rook(EPieceColor::Black);

    //if (bishop.CanMove(startPos, endPos, board) == false || rook.CanMove(startPos, endPos, board) == false)
    //    return false;

    return ( (startPos.first==endPos.first ^ startPos.second==endPos.second) || (std::abs(startPos.first -endPos.first)==std::abs(startPos.second- endPos.second)) );
}