#include "Board.h"
#include <stdexcept>
#include<iostream>

Board::Board() {
	InitializeBoard();
}

Board::Board(std::vector<std::pair<PiecePtr, Position>> piecePos)
{
	//InitializeBoard();
	for (auto it : piecePos)
	{
		switch (it.first->GetType())
		{
		case EPieceType::Rook:
			m_board[it.second.first][it.second.second] = std::make_shared<Rook>(it.first->GetColor());
			break;
		case EPieceType::Bishop:
			m_board[it.second.first][it.second.second] = std::make_shared<Bishop>(it.first->GetColor());
			break;
		case EPieceType::Pawn:
			m_board[it.second.first][it.second.second] = std::make_shared<Pawn>(it.first->GetColor());
			break;
		case EPieceType::King:
			m_board[it.second.first][it.second.second] = std::make_shared<King>(it.first->GetColor());
			break;
		case EPieceType::Knight:
			m_board[it.second.first][it.second.second] = std::make_shared<Knight>(it.first->GetColor());
			break;
		case EPieceType::Queen:
			m_board[it.second.first][it.second.second] = std::make_shared<Queen>(it.first->GetColor());
			break;
		default:
			break;
		}
	}
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
	piece->GetColor();
	return true;
}

BoardType Board::GetBoard() const
{
	return m_board;
}

void Board::SetPiece(Position pos, EPieceColor color, EPieceType type)
{

	switch (type)
	{
	case EPieceType::Rook:
		m_board[pos.first][pos.second] = std::make_shared<Rook>(color);
		break;
	case EPieceType::Bishop:
		m_board[pos.first][pos.second] = std::make_shared<Bishop>(color);
		break;
	case EPieceType::Pawn:
		m_board[pos.first][pos.second] = std::make_shared<Pawn>(color);
		break;
	case EPieceType::King:
		m_board[pos.first][pos.second] = std::make_shared<King>(color);
		break;
	case EPieceType::Knight:
		m_board[pos.first][pos.second] = std::make_shared<Knight>(color);
		break;
	case EPieceType::Queen:
		m_board[pos.first][pos.second] = std::make_shared<Queen>(color);
		break;
	default:
		break;
	}
}

bool Board::IsKingInCheck(Position startPos, Position endPos, EPieceColor pieceColor) const
{
	Position kingPos;
	//search king position on board
	bool found = 0;
	for (int i = 1; i <= 8 && found == 0; i++)
	{
		for (int j = 1; j <= 8 && found == 0; j++)
		{
			if (m_board[i][j] != nullptr && m_board[i][j]->GetColor() == pieceColor && m_board[i][j]->GetType() == EPieceType::King)
			{
				kingPos.first = i;
				kingPos.second = j;
				found = 1;
			}
		}
	}

	//checking Rook
	int i = kingPos.first + 1;
	while (i <= 8)
	{
		if (i == endPos.first && kingPos.second == endPos.second)
			break;
		if (!(i == startPos.first && kingPos.second == startPos.second))
			if (m_board[i][kingPos.second] != nullptr)
			{
				if (m_board[i][kingPos.second]->GetColor() != pieceColor && (m_board[i][kingPos.second]->GetType() == EPieceType::Rook || m_board[i][kingPos.second]->GetType() == EPieceType::Queen))
					return true;
				break;
			}
		i++;
	}

	i = kingPos.first - 1;
	while (i >= 1)
	{

		if (i == endPos.first && kingPos.second == endPos.second)
			break;
		if (!(i == startPos.first && kingPos.second == startPos.second))
			if (m_board[i][kingPos.second] != nullptr)
			{
				if (m_board[i][kingPos.second]->GetColor() != pieceColor && (m_board[i][kingPos.second]->GetType() == EPieceType::Rook || m_board[i][kingPos.second]->GetType() == EPieceType::Queen))
					return true;
				break;
			}
		i--;
	}

	i = kingPos.second + 1;
	while (i <= 8)
	{
		if (i == endPos.second && kingPos.first == endPos.first)
			break;
		if (!(i == startPos.second && kingPos.first == startPos.first))
			if (m_board[kingPos.first][i] != nullptr)
			{
				if (m_board[kingPos.first][i]->GetColor() != pieceColor && (m_board[kingPos.first][i]->GetType() == EPieceType::Rook || m_board[kingPos.first][i]->GetType() == EPieceType::Queen))
					return true;
				break;
			}
		i++;
	}

	i = kingPos.second - 1;
	while (i >= 1)
	{
		if (i == endPos.second && kingPos.first == endPos.first)
			break;
		if (!(i == startPos.second && kingPos.first == startPos.first))
			if (m_board[kingPos.first][i] != nullptr)
			{
				if (m_board[kingPos.first][i]->GetColor() != pieceColor && (m_board[kingPos.first][i]->GetType() == EPieceType::Rook || m_board[kingPos.first][i]->GetType() == EPieceType::Queen))
					return true;
				break;
			}
		i--;
	}

	//checking Bishop threat

	int currentRow = kingPos.first - 1;
	int currentCol = kingPos.second + 1;

	while (currentCol <= 8 && currentRow >= 1)
	{
		if (currentCol == endPos.second && currentRow == endPos.first)
			break;
		if (!(currentCol == startPos.second && currentRow == startPos.first))
			if (m_board[currentRow][currentCol] != nullptr && m_board[currentRow][currentCol]->GetColor() != pieceColor && (m_board[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_board[currentRow][currentCol]->GetType() == EPieceType::Queen))
				return true;

		currentRow--;
		currentCol++;
	}

	currentRow = kingPos.first + 1;
	currentCol = kingPos.second + 1;

	while (currentCol <= 8 && currentRow <= 8)
	{
		if (currentCol == endPos.second && currentRow == endPos.first)
			break;
		if (!(currentCol == startPos.second && currentRow == startPos.first))
			if (m_board[currentRow][currentCol] != nullptr && m_board[currentRow][currentCol]->GetColor() != pieceColor && (m_board[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_board[currentRow][currentCol]->GetType() == EPieceType::Queen))
				return true;

		currentRow++;
		currentCol++;
	}

	currentRow = kingPos.first + 1;
	currentCol = kingPos.second - 1;

	while (currentCol >= 1 && currentRow <= 8)
	{
		if (currentCol == endPos.second && currentRow == endPos.first)
			break;
		if (!(currentCol == startPos.second && currentRow == startPos.first))
			if (m_board[currentRow][currentCol] != nullptr && m_board[currentRow][currentCol]->GetColor() != pieceColor && (m_board[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_board[currentRow][currentCol]->GetType() == EPieceType::Queen))
				return true;

		currentRow++;
		currentCol--;
	}

	currentRow = kingPos.first - 1;
	currentCol = kingPos.second - 1;

	while (currentCol >= 1 && currentRow >= 1)
	{
		if (currentCol == endPos.second && currentRow == endPos.first)
			break;
		if (!(currentCol == startPos.second && currentRow == startPos.first))
			if (m_board[currentRow][currentCol] != nullptr && m_board[currentRow][currentCol]->GetColor() != pieceColor && (m_board[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_board[currentRow][currentCol]->GetType() == EPieceType::Queen))
				return true;

		currentRow--;
		currentCol--;
	}

	//check pawn threat
	if (pieceColor == EPieceColor::White)
	{
		if (kingPos.first + 1 <= 8)
		{
			if (kingPos.second - 1 >= 1 && m_board[kingPos.first + 1][kingPos.second - 1] != nullptr && m_board[kingPos.first + 1][kingPos.second - 1]->GetColor() != pieceColor && (kingPos.first + 1 != endPos.first || kingPos.second - 1 != endPos.second))
				return true;

			if (kingPos.second + 1 <= 8 && m_board[kingPos.first + 1][kingPos.second + 1] != nullptr && m_board[kingPos.first + 1][kingPos.second + 1]->GetColor() != pieceColor && (kingPos.first + 1 != endPos.first || kingPos.second + 1 != endPos.second))
				return true;
		}
	}

	if (pieceColor == EPieceColor::Black)
	{
		if (kingPos.first - 1 >= 1)
		{
			if (kingPos.second - 1 >= 1 && m_board[kingPos.first - 1][kingPos.second - 1] != nullptr && m_board[kingPos.first - 1][kingPos.second - 1]->GetColor() != pieceColor && (kingPos.first -1 != endPos.first || kingPos.second - 1 != endPos.second))
				return true;

			if (kingPos.second + 1 <= 8 && m_board[kingPos.first - 1][kingPos.second + 1] != nullptr && m_board[kingPos.first - 1][kingPos.second + 1]->GetColor() != pieceColor && (kingPos.first - 1 != endPos.first || kingPos.second + 1 != endPos.second))
				return true;
		}
	}

	//check knight threat

	for(int i=kingPos.first-2;i<=kingPos.first+2;i++)
		for (int j = kingPos.second - 2; j <= kingPos.second + 2; j++)
		{
			if (abs(kingPos.first - i) == 2 && abs(kingPos.second - j) == 1 || abs(kingPos.first - i) == 1 && abs(kingPos.second - j) == 2)
				if (m_board[i][j] != nullptr && m_board[i][j]->GetColor() != pieceColor && m_board[i][j]->GetType() == EPieceType::Knight && (i!=endPos.first || j!=endPos.second))
					return true;
		}
	
	return false;
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