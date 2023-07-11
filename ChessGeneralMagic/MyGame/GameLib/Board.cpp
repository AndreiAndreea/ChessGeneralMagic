#include "Board.h"
#include <stdexcept>

Board::Board() {
	resetBoard();
}

Spot* Board::getSpot(int x, int y) {
	if (x < 1 || x > 8 || y < 1 || y > 8)
	{
		throw std::out_of_range("The position is invalid.");
	}

	return &board[x][y];
}

void Board::resetBoard() {

	// initializing the board with spots(each square)
	for (int x = 1; x <= 8; x++) {
		for (int y = 1; y <= 8; y++) {
			board[x][y].setPosition(x, y);
		}
	}

	//initializing the white pieces 
	board[1][1].setPiece(new Rook(true));
	board[1][8].setPiece(new Rook(true));

	board[1][2].setPiece(new Knight(true));
	board[1][7].setPiece(new Knight(true));

	board[1][3].setPiece(new Bishop(true));
	board[1][6].setPiece(new Bishop(true));

	board[1][4].setPiece(new Qween(true));
	board[1][5].setPiece((new King(true)));

	for (int i = 1; i<=8; i++)
	{
		board[2][i].setPiece(new Pawn(true))
	}

	// initializing the black pieces
	board[8][1].setPiece(new Rook(false));
	board[8][8].setPiece(new Rook(false));

	board[8][2].setPiece(new Knight(false));
	board[8][7].setPiece(new Knight(false));

	board[8][3].setPiece(new Bishop(false));
	board[8][6].setPiece(new Bishop(false));

	board[8][4].setPiece(new Qween(false));
	board[8][5].setPiece((new King(false)));

	for (int i = 1; i <= 8; i++)
	{
		board[7][i].setPiece(new Pawn(false))
	}

	//and the rest of the positions
}
