#include "gtest/gtest.h"

#include "King.h"
#include "Board.h"

class KingTest : public testing::Test {

	void SetUp() override
	{
		king = new King(EPieceColor::White);
	}

	void TearDown() override
	{
		delete king;
	}

protected:
	King* king;

};

TEST_F(KingTest, InvalidMove) {
	Board board;
	board.SetPiece(Position(3, 3), EPieceColor::White, EPieceType::King);

	EXPECT_FALSE(king->CanMove(Position(3, 3), Position(2, 3), board));
}


TEST_F(KingTest, InvalidMove1) 
{
	Board board;
	std::vector<std::pair<Position, Position>> possibleMoves = { {Position(3,3), Position(1,4)}, {Position(3,3), Position(5,5)},
		{Position(0,3), Position(0,5)} , {Position(7,0), Position(7,1)} };

	for (auto it : possibleMoves)
	{
		board.SetPiece(it.first, EPieceColor::White, EPieceType::King);
		EXPECT_FALSE(king->CanMove(it.first, it.second, board));
	}
}


TEST_F(KingTest, ValidMoveCheck2)
{
	Board board;
	board.SetPiece(Position(3, 2), EPieceColor::White, EPieceType::King);
	board.SetPiece(Position(4, 3), EPieceColor::Black, EPieceType::Queen);

	EXPECT_TRUE(king->CanMove(Position(3, 2), Position(4, 3), board));
}

TEST_F(KingTest, InValidMoveCheck) {
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::White, EPieceType::King);
	board.SetPiece(Position(3, 4), EPieceColor::Black, EPieceType::Bishop);
	board.SetPiece(Position(4, 4), EPieceColor::Black, EPieceType::Rook);

	EXPECT_FALSE(king->CanMove(Position(5, 5), Position(5, 4), board));
}

TEST_F(KingTest, InValidMoveCheck2) {
	Board board;
	board.SetPiece(Position(4, 6), EPieceColor::White, EPieceType::King);
	board.SetPiece(Position(2, 7), EPieceColor::White, EPieceType::Bishop);
	board.SetPiece(Position(3, 4), EPieceColor::Black, EPieceType::Rook);

	EXPECT_FALSE(king->CanMove(Position(4, 6), Position(3, 6), board));
}

TEST_F(KingTest, InValidMoveCheck3) {
	Board board;
	board.SetPiece(Position(5, 4), EPieceColor::White, EPieceType::King);
	board.SetPiece(Position(7, 5), EPieceColor::Black, EPieceType::Queen);
	board.SetPiece(Position(3, 4), EPieceColor::Black, EPieceType::Rook);

	EXPECT_FALSE(king->CanMove(Position(5, 4), Position(5, 5), board));
}

TEST_F(KingTest, InValidMoveCheck4) {
	Board board;
	board.SetPiece(Position(3, 2), EPieceColor::White, EPieceType::King);
	board.SetPiece(Position(4, 3), EPieceColor::Black, EPieceType::Queen);
	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Knight);

	EXPECT_FALSE(king->CanMove(Position(3, 2), Position(4, 3), board));
}

TEST_F(KingTest, ValidMoveCheck3) {
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::White, EPieceType::King);
	board.SetPiece(Position(3, 4), EPieceColor::Black, EPieceType::Bishop);
	board.SetPiece(Position(6, 6), EPieceColor::Black, EPieceType::Rook);

	EXPECT_TRUE(king->CanMove(Position(5, 5), Position(5, 4), board));
}

TEST_F(KingTest, ValidCastlingSmall) {
	Board board;
	board.SetPieceToNullptr(Position(8, 2));
	board.SetPieceToNullptr(Position(8, 3));
	board.SetPieceToNullptr(Position(8, 4));
	board.SetPieceToNullptr(Position(8, 6));
	board.SetPieceToNullptr(Position(8, 7));

	EXPECT_TRUE(king->CanMove(Position(8,5), Position(8,7), board));
}

TEST_F(KingTest, ValidCastlingBig) {
	Board board;
	board.SetPieceToNullptr(Position(8, 2));
	board.SetPieceToNullptr(Position(8, 3));
	board.SetPieceToNullptr(Position(8, 4));
	board.SetPieceToNullptr(Position(8, 6));
	board.SetPieceToNullptr(Position(8, 7));

	EXPECT_TRUE(king->CanMove(Position(8, 5), Position(8, 3), board));
}

TEST_F(KingTest, InvalidCastlingSmall) {
	Board board;
	board.SetPieceToNullptr(Position(8, 2));
	board.SetPieceToNullptr(Position(8, 3));
	board.SetPieceToNullptr(Position(8, 4));
	board.SetPieceToNullptr(Position(8, 6));
	board.SetPieceToNullptr(Position(8, 7));
	board.SetPieceToNullptr(Position(7, 6));
	board.SetPiece(Position(5, 6), EPieceColor::Black, EPieceType::Queen);
	EXPECT_FALSE(king->CanMove(Position(8, 5), Position(8, 7), board));
}

TEST_F(KingTest, InvalidCastlingSmall1) {
	Board board;
	board.SetPieceToNullptr(Position(8, 2));
	board.SetPieceToNullptr(Position(8, 3));
	board.SetPieceToNullptr(Position(8, 4));
	board.SetPieceToNullptr(Position(8, 6));
	board.SetPieceToNullptr(Position(8, 7));
	board.SetPieceToNullptr(Position(7, 5));
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Queen);
	EXPECT_FALSE(king->CanMove(Position(8, 5), Position(8, 7), board));
}

TEST_F(KingTest, InvalidCastlingBig) {
	Board board;
	board.SetPieceToNullptr(Position(8, 2));
	board.SetPieceToNullptr(Position(8, 3));
	board.SetPieceToNullptr(Position(8, 4));
	board.SetPieceToNullptr(Position(8, 6));
	board.SetPieceToNullptr(Position(8, 7));
	board.SetPieceToNullptr(Position(7, 3));
	board.SetPiece(Position(5, 3), EPieceColor::Black, EPieceType::Queen);
	EXPECT_FALSE(king->CanMove(Position(8, 5), Position(8, 3), board));
}
