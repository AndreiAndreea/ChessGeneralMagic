#include "Board.h"
#include <stdexcept>

Board::Board() {
	resetBoard();
}

Spot* Board::getSpot(int x, int y) {
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
	{
		throw std::out_of_range("The position is invalid.");
	}

	return &board[x][y];
}

void Board::resetBoard() {

	// initializing the board with spots(each square)
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			board[x][y].setPosition(x, y);
		}
	}

	//initializing the white pieces 
	//board[0][0].setPiece(new Rook(true));
	//board[0][1].setPiece(new Knight(true));
	//board[0][2].setPiece(new Bishop(true));
	//and the rest of the positions

	// initializing the black pieces
	//board[7][0].setPiece(new Rook(false));
	//board[7][1].setPiece(new Knight(false));
	//board[7][2].setPiece(new Bishop(false));
	//and the rest of the positions
}