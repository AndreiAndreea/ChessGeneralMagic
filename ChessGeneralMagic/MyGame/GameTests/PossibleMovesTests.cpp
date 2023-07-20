#include "gtest/gtest.h"   

#include "Pawn.h"
#include "Board.h"
#include "Piece.h"


//possible moves for bishop
TEST(PossibleMovesTest, ValidMovesPosibilitiesBishop) 
{
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Bishop);
	std::vector<Position> vector = { Position(4,6),Position(3,7), Position(6,6),  Position(7,7), Position(6,4),
		 Position(7,3), Position(4,4),Position(3,3) };
	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board) , vector);
}

TEST(PossibleMovesTest, ValidMovesPosibilitiesBishop2)
{
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Bishop);
	board.SetPiece(Position(3, 7), EPieceColor::Black, EPieceType::Rook);
	std::vector<Position> vector = { Position(4,6), Position(6,6),  Position(7,7), Position(6,4),
		 Position(7,3), Position(4,4),Position(3,3) };
	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board), vector);
}

TEST(PossibleMovesTest, ValidMovesPosibilitiesBishop3)
{
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Bishop);
	board.SetPiece(Position(3, 7), EPieceColor::White, EPieceType::Rook);
	std::vector<Position> vector = { Position(4,6),Position(3,7), Position(6,6),  Position(7,7), Position(6,4),
		 Position(7,3), Position(4,4),Position(3,3) };
	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board), vector);
}

//possible moves for knight

TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight)
{
	Board board;
	board.SetPiece(Position(4, 4), EPieceColor::White, EPieceType::Knight);
	std::vector<Position> vector = { Position(2,3), Position(2, 5), Position(3,2),Position(3,6),Position(5,2),Position(5,6),
		Position(6,3),Position(6,5)};
	EXPECT_EQ(board.GetBoard()[4][4]->GetPossibleMoves(Position(4, 4), board), vector);
}

TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight2)
{
	Board board;
	board.SetPiece(Position(4, 4), EPieceColor::Black, EPieceType::Knight);
	std::vector<Position> vector = {Position(3,2),Position(3,6),Position(5,2),Position(5,6),
		Position(6,3),Position(6,5) };
	EXPECT_EQ(board.GetBoard()[4][4]->GetPossibleMoves(Position(4, 4), board), vector);
}

//knight in corner
TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight3)
{
	Board board;
	board.SetPiece(Position(1, 1), EPieceColor::Black, EPieceType::Knight);
	std::vector<Position> vector = {Position(3,2)};
	EXPECT_EQ(board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board), vector);
}

TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight4)
{
	Board board;
	board.SetPiece(Position(1, 1), EPieceColor::White, EPieceType::Knight);
	std::vector<Position> vector = { Position(2, 3), Position(3,2) };
	EXPECT_EQ(board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board), vector);
}

//on the right side
TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight5)
{
	Board board;
	board.SetPiece(Position(4, 8), EPieceColor::White, EPieceType::Knight);
	std::vector<Position> vector = { Position(2, 7), Position(3,6),Position(5,6),Position(6,7) };
	EXPECT_EQ(board.GetBoard()[4][8]->GetPossibleMoves(Position(4, 8), board), vector);
}
TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight6)
{
	Board board;
	board.SetPiece(Position(4, 8), EPieceColor::Black, EPieceType::Knight);
	std::vector<Position> vector = {Position(3,6),Position(5,6),Position(6,7) };
	EXPECT_EQ(board.GetBoard()[4][8]->GetPossibleMoves(Position(4, 8), board), vector);
}
//possible moves for king
TEST(PossibleMovesTest, ValidMovesPosibilitiesKing)
{
	Board board;
	board.SetPiece(Position(4, 8), EPieceColor::White, EPieceType::King);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Rook);
	std::vector<Position> vector = {Position(4,7), Position(5,7), Position(5,8) };
	auto vect1 = board.GetBoard()[4][8]->GetPossibleMoves(Position(4, 8), board);
	EXPECT_EQ(board.GetBoard()[4][8]->GetPossibleMoves(Position(4, 8), board), vector);
}

TEST(PossibleMovesTest, ValidMovesPosibilitiesKing2)

{
	Board board;
	board.SetPiece(Position(6, 8), EPieceColor::White, EPieceType::King);
	std::vector<Position> vector = { Position(5,7) , Position(5,8) ,Position(6,7) };
	auto vect1 = board.GetBoard()[6][8]->GetPossibleMoves(Position(6, 8), board);
	EXPECT_EQ(board.GetBoard()[6][8]->GetPossibleMoves(Position(6, 8), board), vector);
}



TEST(PossibleMovesTest, ValidMovesPosibilitiesKing4)
{
	Board board(0);
	board.SetPiece(Position(1, 5), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(1, 4), EPieceColor::Black, EPieceType::Queen);
	board.SetPiece(Position(1, 6), EPieceColor::Black, EPieceType::Bishop);
	board.SetPiece(Position(2, 4), EPieceColor::Black, EPieceType::Pawn);
	board.SetPiece(Position(2, 5), EPieceColor::Black, EPieceType::Pawn);
	board.SetPiece(Position(4, 8), EPieceColor::White, EPieceType::Queen);	
	std::vector<Position> vector = {};
	auto vect1 = board.GetBoard()[1][5]->GetPossibleMoves(Position(1, 5), board);
	EXPECT_EQ(board.GetBoard()[1][5]->GetPossibleMoves(Position(1, 5), board), vector);
}

TEST(PossibleMovesTest, ValidMovesPosibilitiesKing3)
{
	Board board;
	board.SetPiece(Position(4, 6), EPieceColor::Black, EPieceType::King);
	board.SetPiece(Position(3, 5), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(6, 8), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(3, 6), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(4, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(5, 5), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(5, 6), EPieceColor::White, EPieceType::Pawn);
	board.SetPiece(Position(4, 7), EPieceColor::White, EPieceType::Pawn);
	std::vector<Position> vector = { Position(5, 5)};
	auto vect1 = board.GetBoard()[4][6]->GetPossibleMoves(Position(4, 6), board);
	//incorrect vect1 
	EXPECT_EQ(board.GetBoard()[4][6]->GetPossibleMoves(Position(4, 6), board), vector);
}

//possible moves for rook
TEST(PossibleMovesTest, ValidMovesPosibilitiesRook)
{
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Rook);
	std::vector<Position> vector = { Position(6,5),Position(7,5), Position(5,4),Position(5,3),Position(5,2),Position(5,1),
		Position(4,5),Position(3,5) ,Position(5,6),Position(5,7) ,Position(5,8) };
	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board), vector);
}

//rook in corner
TEST(PossibleMovesTest, ValidMovesPosibilitiesRook1)
{
	Board board;
	board.SetPiece(Position(1, 1), EPieceColor::Black, EPieceType::Rook);
	std::vector<Position> vector = {};
	std::vector<Position> vector1 = board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board);
	EXPECT_EQ(board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board), vector);
}

TEST(PossibleMovesTest, ValidMovesPosibilitiesRook2)
{
	Board board;
	board.SetPiece(Position(1, 1), EPieceColor::White, EPieceType::Rook);
	std::vector<Position> vector = { Position(2,1), Position(1,2) };
	std::vector<Position> vector1 = board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board);
	EXPECT_EQ(board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board), vector);
}


//possible moves for queen
TEST(PossibleMovesTest, ValidMovesPosibilitiesQueen)
{
	Board board;
	board.SetPiece(Position(5, 1), EPieceColor::White, EPieceType::Queen);
	board.SetPiece(Position(5, 4), EPieceColor::White, EPieceType::Rook);
	board.SetPiece(Position(3,3), EPieceColor::Black, EPieceType::Bishop);

	std::vector<Position> vector = { Position(6, 1),Position(4, 1),Position(3, 1),Position(2, 1),Position(5, 2),Position(5, 3),
		Position(4,2),Position(3, 3),Position(6,2) };
	EXPECT_EQ(board.GetBoard()[5][1]->GetPossibleMoves(Position(5, 1), board), vector);
}