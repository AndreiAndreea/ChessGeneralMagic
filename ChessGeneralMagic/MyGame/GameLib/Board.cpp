#include "Board.h"
#include <stdexcept>

Board::Board() {
	InitializeBoard();
}

void Board::InitializeBoard() {

	// initializing the board with spots(each square)
	for (int x = 3; x <= 6; x++) {
		for (int y = 1; y <= 8; y++) {
			m_board[x][y]=nullptr;
		}
	}

	//initializing the white pieces 
	//board[1][1].setPiece(new Rook(true));
	//board[1][8].setPiece(new Rook(true));

	//board[1][2].setPiece(new Knight(true));
	//board[1][7].setPiece(new Knight(true));

	//board[1][3].setPiece(new Bishop(true));
	//board[1][6].setPiece(new Bishop(true));

	//board[1][4].setPiece(new Qween(true));
	//board[1][5].setPiece((new King(true)));

	//for (int i = 1; i<=8; i++)
	//{
	//	board[2][i].setPiece(new Pawn(true))
	//}

	// initializing the black pieces
	//board[8][1].setPiece(new Rook(false));
	//board[8][8].setPiece(new Rook(false));

	//board[8][2].setPiece(new Knight(false));
	//board[8][7].setPiece(new Knight(false));

	//board[8][3].setPiece(new Bishop(false));
	//board[8][6].setPiece(new Bishop(false));

	//board[8][4].setPiece(new Qween(false));
	//board[8][5].setPiece((new King(false)));

	//for (int i = 1; i <= 8; i++)
	//{
	//	board[7][i].setPiece(new Pawn(false))
	//}
}

bool Board::MakeMove(Position startPos, Position endPos, Board& board)
{
	auto piece = board.m_board[startPos.first][startPos.second];
	piece->canMove()
	return true;
}
