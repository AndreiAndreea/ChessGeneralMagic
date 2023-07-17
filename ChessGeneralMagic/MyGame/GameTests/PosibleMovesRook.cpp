#include "gtest/gtest.h"   

#include "Pawn.h"
#include "Board.h"
#include "Piece.h"


TEST(PossibleMovesTestRook, ValidMovesPosibilities)
{
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Rook);
	std::vector<Position> vector = {Position(6,5), Position(5,4),Position(5,3),Position(5,2),Position(5,1),
		Position(4,5),Position(3,5),Position(2,5) ,Position(5,6),Position(5,7) ,Position(5,8) };
	std::vector<Position> vector1 = board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board);
	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board), vector);
}

//rook in corner
TEST(PossibleMovesTestRook, ValidMovesPosibilities1)
{
	Board board;
	board.SetPiece(Position(1, 1), EPieceColor::Black, EPieceType::Rook);
	std::vector<Position> vector = { Position(2,1), Position(1,2)};
	std::vector<Position> vector1 = board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board);
	EXPECT_EQ(board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board), vector);
}

TEST(PossibleMovesTestRook, ValidMovesPosibilities2)
{
	Board board;
	board.SetPiece(Position(1, 1), EPieceColor::White, EPieceType::Rook);
	std::vector<Position> vector = {};
	std::vector<Position> vector1 = board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board);
	EXPECT_EQ(board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board), vector);
}