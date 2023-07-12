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
	m_board[1][1] = std::make_shared<Rook>(true);
	m_board[1][8] = std::make_shared<Rook>(true);

	m_board[1][2] = std::make_shared<Knight>(true);
	m_board[1][7] = std::make_shared<Knight>(true);

	m_board[1][3] = std::make_shared<Bishop>(true);
	m_board[1][6] = std::make_shared<Bishop>(true);

	
	m_board[1][4] = std::make_shared<Queen>(true);
	m_board[1][5] = std::make_shared<King>(true);

	for (int i = 1; i<=8; i++)
	{
		m_board[2][i] = std::make_shared<Pawn>(true);
	}

	// initializing the black pieces
	m_board[8][1] = std::make_shared<Rook>(false);
	m_board[8][8] = std::make_shared<Rook>(false);

	m_board[8][2] = std::make_shared<Knight>(true);
	m_board[8][7] = std::make_shared<Knight>(true);

	m_board[8][3] = std::make_shared<Bishop>(true);
	m_board[8][6] = std::make_shared<Bishop>(true);

	m_board[8][4] = std::make_shared<Queen>(true);
	m_board[8][5] = std::make_shared<King>(true);

	for (int i = 1; i <= 8; i++)
	{
		m_board[7][i] = std::make_shared<Pawn>(true);
	}
}

bool Board::MakeMove(Position startPos, Position endPos, Board& board)
{
	auto piece = board.m_board[startPos.first][startPos.second];
	//piece->canMove()
	return true;
}
