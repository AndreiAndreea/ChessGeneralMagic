#include "gtest/gtest.h"   

#include "Pawn.h"
#include "Board.h"
#include "Piece.h"


TEST(PossibleMovesTest, ValidMovesPosibilities) 
{
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Bishop);
	std::vector<Position> vector = { Position(4,6),Position(3,7),Position(2,8),Position(6,6),Position(6,4),
		Position(4,4),Position(3,3),Position(2,2) };
	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board) , vector);
}

TEST(PossibleMovesTest, ValidMovesPosibilities2)
{
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Bishop);
	std::vector<Position> vector = { Position(4,6),Position(3,7),Position(2,8),Position(6,6),Position(6,4),
		Position(4,4),Position(3,3),Position(2,2) };
	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board), vector);
}