#include "gtest/gtest.h"   

#include "Pawn.h"
#include "Board.h"
#include "Piece.h"


//possible moves for bishop
TEST(PossibleMovesTest, ValidMovesPosibilitiesBishop) 
{
	Board board;
	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Bishop);
	std::vector<Position> vector = { Position(4,6),Position(3,7),Position(2,8),Position(6,6),Position(6,4),
		Position(4,4),Position(3,3),Position(2,2) };
	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves() , vector);
}
//
//TEST(PossibleMovesTest, ValidMovesPosibilitiesBishop2)
//{
//	Board board;
//	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Bishop);
//	board.SetPiece(Position(3, 7), EPieceColor::Black, EPieceType::Rook);
//	std::vector<Position> vector = { Position(4,6),Position(6,6),Position(6,4),
//		Position(4,4),Position(3,3),Position(2,2) };
//	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board), vector);
//}
//
//TEST(PossibleMovesTest, ValidMovesPosibilitiesBishop3)
//{
//	Board board;
//	board.SetPiece(Position(5, 5), EPieceColor::Black, EPieceType::Bishop);
//	board.SetPiece(Position(3, 7), EPieceColor::White, EPieceType::Rook);
//	std::vector<Position> vector = { Position(4,6),Position(3,7),Position(6,6),Position(6,4),
//		Position(4,4),Position(3,3),Position(2,2) };
//	EXPECT_EQ(board.GetBoard()[5][5]->GetPossibleMoves(Position(5, 5), board), vector);
//}
//
////possible moves for knight
//
//TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight)
//{
//	Board board;
//	board.SetPiece(Position(4, 4), EPieceColor::White, EPieceType::Knight);
//	std::vector<Position> vector = { Position(3,2),Position(3,6),Position(5,2),Position(5,6),
//		Position(6,3),Position(6,5)};
//	EXPECT_EQ(board.GetBoard()[4][4]->GetPossibleMoves(Position(4, 4), board), vector);
//}
//
//TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight2)
//{
//	Board board;
//	board.SetPiece(Position(4, 4), EPieceColor::Black, EPieceType::Knight);
//	std::vector<Position> vector = { Position(2,3),Position(2,5),Position(3,2),Position(3,6),Position(5,2),Position(5,6),
//		Position(6,3),Position(6,5) };
//	EXPECT_EQ(board.GetBoard()[4][4]->GetPossibleMoves(Position(4, 4), board), vector);
//}
//
////knight in corner
//TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight3)
//{
//	Board board;
//	board.SetPiece(Position(1, 1), EPieceColor::Black, EPieceType::Knight);
//	std::vector<Position> vector = { Position(2,3),Position(3,2)};
//	EXPECT_EQ(board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board), vector);
//}
//
//TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight4)
//{
//	Board board;
//	board.SetPiece(Position(1, 1), EPieceColor::White, EPieceType::Knight);
//	std::vector<Position> vector = { Position(3,2) };
//	EXPECT_EQ(board.GetBoard()[1][1]->GetPossibleMoves(Position(1, 1), board), vector);
//}
//
////on the right side
//TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight5)
//{
//	Board board;
//	board.SetPiece(Position(4, 8), EPieceColor::White, EPieceType::Knight);
//	std::vector<Position> vector = { Position(3,6),Position(5,6),Position(6,7) };
//	EXPECT_EQ(board.GetBoard()[4][8]->GetPossibleMoves(Position(4, 8), board), vector);
//}
//TEST(PossibleMovesTest, ValidMovesPosibilitiesKnight6)
//{
//	Board board;
//	board.SetPiece(Position(4, 8), EPieceColor::Black, EPieceType::Knight);
//	std::vector<Position> vector = { Position(2,7),Position(3,6),Position(5,6),Position(6,7) };
//	EXPECT_EQ(board.GetBoard()[4][8]->GetPossibleMoves(Position(4, 8), board), vector);
//}
////possible moves for king
//TEST(PossibleMovesTest, ValidMovesPosibilitiesKing)
//{
//	Board board;
//	board.SetPiece(Position(4, 8), EPieceColor::White, EPieceType::King);
//	board.SetPiece(Position(3, 5), EPieceColor::Black, EPieceType::Rook);
//	std::vector<Position> vector = {Position(4,7) };
//	EXPECT_EQ(board.GetBoard()[4][8]->GetPossibleMoves(Position(4, 8), board), vector);
//}
//
//TEST(PossibleMovesTest, ValidMovesPosibilitiesKing2)
//{
//	Board board;
//	board.SetPiece(Position(6, 8), EPieceColor::White, EPieceType::King);
//	std::vector<Position> vector = {};
//	EXPECT_EQ(board.GetBoard()[6][8]->GetPossibleMoves(Position(6, 8), board), vector);
//}
//
////possible moves for rook
//TEST(PossibleMovesTest, ValidMovesPosibilitiesRook)
//{
//	Board board;
//	board.SetPiece(Position(5,6), EPieceColor::Black, EPieceType::Rook);
//	board.SetPiece(Position(5, 4), EPieceColor::White, EPieceType::Rook);
//	std::vector<Position> vector = { Position(6, 6), Position(5,5),Position(5,4), Position(4, 6),Position(3, 6),Position(2, 6),Position(5,7),Position(5,8)};
//	EXPECT_EQ(board.GetBoard()[5][6]->GetPossibleMoves(Position(5,6), board), vector);
//}
//
//
////possible moves for queen
//TEST(PossibleMovesTest, ValidMovesPosibilitiesQueen)
//{
//	Board board;
//	board.SetPiece(Position(5, 1), EPieceColor::White, EPieceType::Queen);
//	board.SetPiece(Position(5, 4), EPieceColor::White, EPieceType::Rook);
//	board.SetPiece(Position(3, 3), EPieceColor::Black, EPieceType::Bishop);
//
//	std::vector<Position> vector = { Position(6, 1),Position(7, 1),Position(4, 1),Position(3, 1),Position(5, 2),Position(5, 3),
//		Position(4,2),Position(3, 3),Position(6,2),Position(7,3) };
//	EXPECT_EQ(board.GetBoard()[5][1]->GetPossibleMoves(Position(5, 1), board), vector);
//}
//
//TEST(PossibleMovesTest, ValidMovesPosibilitiesQueen2)
//{
//	Board board;
//	board.SetPiece(Position(5, 4), EPieceColor::White, EPieceType::Queen);
//	board.SetPiece(Position(5, 7), EPieceColor::Black, EPieceType::Rook);
//
//	std::vector<Position> vector = { Position(6, 4),Position(7, 4),Position(5, 3),Position(5, 2),Position(5, 1),Position(4, 4),
//		Position(3,4),Position(5, 5),Position(5,6),Position(5,7),Position(4,5),Position(3,6),Position(6,5),Position(7,6),
//		Position(6,3),Position(7,2),Position(4,3),Position(3,2) };
//	EXPECT_EQ(board.GetBoard()[5][4]->GetPossibleMoves(Position(5, 4), board), vector);
//}
//
////one and two steps upwards
//TEST(PossibleMovesTest, ValidMovesPosibilitiesPawn)
//{
//	Board board;
//	board.SetPiece(Position(7,7), EPieceColor::Black, EPieceType::Pawn);
//
//	std::vector<Position> vector = { Position(6, 7),Position(5,7) };
//	EXPECT_EQ(board.GetBoard()[7][7]->GetPossibleMoves(Position(7, 7), board), vector);
//}
//
//TEST(PossibleMovesTest, ValidMovesPosibilitiesPawn2)
//{
//	Board board;
//	board.SetPiece(Position(7, 7), EPieceColor::Black, EPieceType::Pawn);
//	board.SetPiece(Position(6, 6), EPieceColor::White, EPieceType::Rook);
//	board.SetPiece(Position(6, 8), EPieceColor::White, EPieceType::Rook);
//
//	std::vector<Position> vector = { Position(6, 7),Position(6,8),Position(6,6),Position(5,7) };
//	EXPECT_EQ(board.GetBoard()[7][7]->GetPossibleMoves(Position(7, 7), board), vector);
//}