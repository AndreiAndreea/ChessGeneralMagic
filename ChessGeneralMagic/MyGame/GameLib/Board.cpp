#include "Board.h"
#include <stdexcept>
#include<iostream>

Board::Board() {
	InitializeBoard();
}

void Board::InitializeBoard() {

	// initializing the board with spots(each square)

	m_board.resize(9);
	for (int i = 1; i <= 8; i++)
	{
		m_board[i].resize(9);
	}

	for (int x = 3; x <= 6; x++) {
		for (int y = 1; y <= 8; y++) {
			m_board[x][y] = nullptr;
		}
	}

	//initializing the white pieces 
	m_board[1][1] = std::make_shared<Rook>(EPieceColor::White);
	m_board[1][8] = std::make_shared<Rook>(EPieceColor::White);

	m_board[1][2] = std::make_shared<Knight>(EPieceColor::White);
	m_board[1][7] = std::make_shared<Knight>(EPieceColor::White);

	m_board[1][3] = std::make_shared<Bishop>(EPieceColor::White);
	m_board[1][6] = std::make_shared<Bishop>(EPieceColor::White);


	m_board[1][4] = std::make_shared<Queen>(EPieceColor::White);
	m_board[1][5] = std::make_shared<King>(EPieceColor::White);

	for (int i = 1; i <= 8; i++)
	{
		m_board[2][i] = std::make_shared<Pawn>(EPieceColor::White);
	}

	// initializing the black pieces
	m_board[8][1] = std::make_shared<Rook>(EPieceColor::Black);
	m_board[8][8] = std::make_shared<Rook>(EPieceColor::Black);

	m_board[8][2] = std::make_shared<Knight>(EPieceColor::Black);
	m_board[8][7] = std::make_shared<Knight>(EPieceColor::Black);

	m_board[8][3] = std::make_shared<Bishop>(EPieceColor::Black);
	m_board[8][6] = std::make_shared<Bishop>(EPieceColor::Black);

	m_board[8][4] = std::make_shared<Queen>(EPieceColor::Black);
	m_board[8][5] = std::make_shared<King>(EPieceColor::Black);

	for (int i = 1; i <= 8; i++)
	{
		m_board[7][i] = std::make_shared<Pawn>(EPieceColor::Black);
	}
}

bool Board::MakeMove(Position startPos, Position endPos)
{
	auto piece = m_board[startPos.first][startPos.second];
	//daca se poate muta piesa + daca nu ramane regele in sah
	return true;
}

BoardType Board::GetBoard() const
{
	return m_board;
}


//void Board::printBoard()
//{
//	for (int x = 1; x <= 8; x++) {
//		for (int y = 1; y <= 8; y++) {
//			if (m_board[x][y] == nullptr) {
//				std::cout << "0 ";
//			}
//			else {
//				std::cout<<m_board[x][y]->GetType()<<" ";
//			}
//		}
//		std::cout << std::endl;
//	}
//}