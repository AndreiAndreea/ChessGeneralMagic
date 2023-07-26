
#include "Board.h"

#include "KingLeftInCheckException.h"
#include "InvalidMovingPatternException.h"

#include <stdexcept>
#include<iostream>
#include <cstring>

Board::Board() {
	InitializeBoard();
}

static EPieceType GetType(char c)
{
	static const EPieceType TYPES[] = { EPieceType::Pawn, EPieceType::Rook, EPieceType::Knight, EPieceType::Bishop, EPieceType::Queen, EPieceType::King };
	c = toupper(c);
	char str[] = "PRNBQK";
	char* p = strchr(str, c);

	return TYPES[p - str];
}

Board::Board(ConfigMatrix board)
{
	m_board.resize(8);
	for (int i = 0; i < 8; i++)
	{
		m_board[i].resize(8);
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			EPieceColor color;
			EPieceType type;

			if (board[i][j] != '-')
			{
				type = GetType(board[i][j]);

				color = board[i][j] > 91 ? EPieceColor::White : EPieceColor::Black;

				m_board[i][j] = Piece::Produce(type, color);

			}
			else
				m_board[i][j] = nullptr;
		}
	}

}

Board::Board(int)
{
	m_board.resize(8);
	for (int i = 0; i < 8; i++)
	{
		m_board[i].resize(8);
	}

	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			m_board[x][y] = nullptr;

}

Board::Board(const Board& ob)
{
	m_board = ob.GetBoard();
}

void Board::InitializeBoard()
{
	m_board.resize(8);
	for (int i = 0; i < 8; i++)
	{
		m_board[i].resize(8);
	}

	// initializing the empty spaces on the board

	for (int x = 2; x < 6; x++)
		for (int y = 0; y < 8; y++)
			m_board[x][y] = nullptr;

	//initializing the pieces 

	std::vector<EPieceType> TYPES = { EPieceType::Rook, EPieceType::Knight, EPieceType::Bishop, EPieceType::Queen, EPieceType::King, EPieceType::Bishop, EPieceType::Knight, EPieceType::Rook };

	for (int i = 0; i < 8; i++)
	{
		m_board[0][i] = Piece::Produce(TYPES[i], EPieceColor::Black);
		m_board[7][i] = Piece::Produce(TYPES[i], EPieceColor::White);
	}

	for (int i = 0; i < 8; i++)
	{
		m_board[1][i] = Piece::Produce(EPieceType::Pawn, EPieceColor::Black);
		m_board[6][i] = Piece::Produce(EPieceType::Pawn, EPieceColor::White);
	}
}

PieceMatrix Board::GetBoard() const
{
	return m_board;
}

ConfigMovesVesct Board::GetMovesVect() const
{
	return m_movesMade;
}

PositionList Board::GetPossibleMoves(Position pos) const
{
	if (m_board[pos.first][pos.second])
		return m_board[pos.first][pos.second]->GetPossibleMoves(pos, false, *this);
	return {};
}

void Board::SetPiece(const Position& pos, EPieceColor color, EPieceType type)
{
	m_board[pos.first][pos.second] = Piece::Produce(type, color);
}

void Board::SetPieceToNullptr(const Position& pos)
{
	m_board[pos.first][pos.second] = nullptr;
}

void Board::AddToMoves(Position startPos, Position endPos, EPieceColor color)
{
	m_movesMade[(int)color].push_back(std::make_pair(startPos, endPos));
}

void Board::MoveRookForCastling(int castlingType, EPieceColor color)
{
	int i = (int)color ? 0 : 7;
	int start = castlingType < 0 ? 7 : 0;
	int end = castlingType < 0 ? 5 : 3;

	SetPiece(Position(i, end), color, EPieceType::Rook);
	SetPieceToNullptr(Position(i, start));
}

std::bitset<256> Board::GenerateBitset()
{
	int k = 0;
	std::bitset<256> currentBitBoard;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				auto color = (int)m_board[i][j]->GetColor();
				auto type = (int)m_board[i][j]->GetType();

				std::bitset<3> binary(type);
				auto stringType = binary.to_string();

				currentBitBoard[4 * k] = color;
				currentBitBoard[4 * k + 1] = stringType[2] - '0';
				currentBitBoard[4 * k + 2] = stringType[1] - '0';
				currentBitBoard[4 * k + 3] = stringType[0] - '0';

			}
			else
			{
				currentBitBoard[4 * k] = 1;
				currentBitBoard[4 * k + 1] = 1;
				currentBitBoard[4 * k + 2] = 1;
				currentBitBoard[4 * k + 3] = 1;
			}
			k++;
		}
	}
	return currentBitBoard;
}

bool Board::MakeMove(const Position& startPos, const Position& endPos)
{
	auto piece = m_board[startPos.first][startPos.second];
	auto color = piece->GetColor();
	auto type = piece->GetType();

	if (piece->CanMove(startPos, endPos, false, *this))
	{
		if (type != EPieceType::King)
		{
			if (IsKingLeftInCheck(startPos, endPos, color))
			{
				throw KingLeftInCheckException();
			}
		}

		SetPiece(endPos, color, type);
		SetPieceToNullptr(startPos);
		m_movesMade[(int)color].push_back(std::make_pair(startPos, endPos));

		// CASTLING

		if (type == EPieceType::King)
		{
			if (abs(startPos.second - endPos.second) == 2)
				MoveRookForCastling(startPos.second - endPos.second, color);

			//king move for castling
			CastlingPossible[(int)color] = { false, false };
		}

		if (type == EPieceType::Rook)
		{
			if (startPos.second == 0)
				CastlingPossible[(int)color][0] = false;
			if (startPos.second == 7)
				CastlingPossible[(int)color][1] = false;
		}

		return true;
	}
	throw InvalidMovingPatternException();
}

bool Board::IsPieceColor(Position pos, EPieceColor color) const
{
	auto piece = m_board[pos.first][pos.second];

	return piece && piece->GetColor() == color;
}


static bool IsOpposite(PiecePtr piece, EPieceColor color, std::vector<EPieceType> types)
{
	return piece && piece->IsOpposite(color, { EPieceType::Bishop, EPieceType::Queen });
}

bool Board::IsKingLeftInCheck(const Position& startPos, const Position& endPos, EPieceColor pieceColor) const
{
	Position kingPos;

	//search king position on board
	bool found = 0;
	for (int i = 0; i < 8 && found == 0; i++)
	{
		for (int j = 0; j < 8 && found == 0; j++)
		{
			if (m_board[i][j] && m_board[i][j]->Is(EPieceType::King, pieceColor))
			{
				kingPos.first = i;
				kingPos.second = j;
				found = 1;
			}
		}
	}

	if (kingPos.first == 0 && kingPos.second == 0)
		found = 1;

	//checking Rook
	int i = kingPos.first + 1;
	while (i < 8)
	{
		if (i == endPos.first && kingPos.second == endPos.second)
			break;
		auto piece = m_board[i][kingPos.second];
		if (!(i == startPos.first && kingPos.second == startPos.second))
			if (piece)
			{
				if (piece->GetColor() != pieceColor && (piece->GetType() == EPieceType::Rook || piece->GetType() == EPieceType::Queen))
					return true;
				break;
			}
		i++;
	}

	i = kingPos.first - 1;
	while (i >= 0)
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
	while (i < 8)
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
	while (i >= 0)
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

	while (currentCol < 8 && currentRow >= 0)
	{
		if (currentCol == endPos.second && currentRow == endPos.first)
			break;

		auto piece = m_board[currentRow][currentCol];
		if (!(currentRow == startPos.first && currentCol == startPos.second))
			//if (IsOpposite(piece, pieceColor, { EPieceType::Bishop, EPieceType::Queen }))
			if (m_board[currentRow][currentCol] != nullptr)
				if (m_board[currentRow][currentCol]->GetColor() != pieceColor && (m_board[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_board[currentRow][currentCol]->GetType() == EPieceType::Queen))
					return true;
				else
					break;

		currentRow--;
		currentCol++;
	}

	currentRow = kingPos.first + 1;
	currentCol = kingPos.second + 1;

	while (currentCol < 8 && currentRow < 8)
	{
		if (currentCol == endPos.second && currentRow == endPos.first)
			break;
		if (!(currentCol == startPos.second && currentRow == startPos.first))
			if (m_board[currentRow][currentCol] != nullptr)
				if (m_board[currentRow][currentCol]->GetColor() != pieceColor && (m_board[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_board[currentRow][currentCol]->GetType() == EPieceType::Queen))
					return true;
				else
					break;

		currentRow++;
		currentCol++;
	}

	currentRow = kingPos.first + 1;
	currentCol = kingPos.second - 1;

	while (currentCol >= 0 && currentRow < 8)
	{
		if (currentCol == endPos.second && currentRow == endPos.first)
			break;
		if (!(currentCol == startPos.second && currentRow == startPos.first))
			if (m_board[currentRow][currentCol] != nullptr)
				if (m_board[currentRow][currentCol]->GetColor() != pieceColor && (m_board[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_board[currentRow][currentCol]->GetType() == EPieceType::Queen))
					return true;
				else
					break;

		currentRow++;
		currentCol--;
	}

	currentRow = kingPos.first - 1;
	currentCol = kingPos.second - 1;

	while (currentCol >= 0 && currentRow >= 0)
	{
		if (currentCol == endPos.second && currentRow == endPos.first)
			break;
		if (!(currentCol == startPos.second && currentRow == startPos.first))
			if (m_board[currentRow][currentCol] != nullptr)
				if (m_board[currentRow][currentCol]->GetColor() != pieceColor && (m_board[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_board[currentRow][currentCol]->GetType() == EPieceType::Queen))
					return true;
				else
					break;

		currentRow--;
		currentCol--;
	}

	//check pawn threat
	if (pieceColor == EPieceColor::Black)
	{
		if (kingPos.first + 1 < 8)
		{
			if (kingPos.second - 1 >= 0 && m_board[kingPos.first + 1][kingPos.second - 1] != nullptr && m_board[kingPos.first + 1][kingPos.second - 1]->GetColor() != pieceColor
				&& (kingPos.first + 1 != endPos.first || kingPos.second - 1 != endPos.second) && m_board[kingPos.first + 1][kingPos.second - 1]->GetType() == EPieceType::Pawn)
				return true;

			if (kingPos.second + 1 < 8 && m_board[kingPos.first + 1][kingPos.second + 1] != nullptr && m_board[kingPos.first + 1][kingPos.second + 1]->GetColor() != pieceColor
				&& (kingPos.first + 1 != endPos.first || kingPos.second + 1 != endPos.second) && m_board[kingPos.first + 1][kingPos.second + 1]->GetType() == EPieceType::Pawn)
				return true;
		}
	}

	if (pieceColor == EPieceColor::White)
	{
		if (kingPos.first - 1 >= 0)
		{
			if (kingPos.second - 1 >= 0 && m_board[kingPos.first - 1][kingPos.second - 1] != nullptr && m_board[kingPos.first - 1][kingPos.second - 1]->GetColor() != pieceColor
				&& (kingPos.first - 1 != endPos.first || kingPos.second - 1 != endPos.second) && m_board[kingPos.first - 1][kingPos.second - 1]->GetType() == EPieceType::Pawn)
				return true;

			if (kingPos.second + 1 < 8 && m_board[kingPos.first - 1][kingPos.second + 1] != nullptr && m_board[kingPos.first - 1][kingPos.second + 1]->GetColor() != pieceColor
				&& (kingPos.first - 1 != endPos.first || kingPos.second + 1 != endPos.second) && m_board[kingPos.first - 1][kingPos.second + 1]->GetType() == EPieceType::Pawn)
				return true;
		}
	}

	//check knight threat
	for (int i = kingPos.first - 2; i <= kingPos.first + 2; i++)
		for (int j = kingPos.second - 2; j <= kingPos.second + 2; j++)
		{
			if (i < 8 && i >= 0 && j < 8 && j >= 0)
				if (abs(kingPos.first - i) == 2 && abs(kingPos.second - j) == 1 || abs(kingPos.first - i) == 1 && abs(kingPos.second - j) == 2)
					if (m_board[i][j] != nullptr && m_board[i][j]->GetColor() != pieceColor && m_board[i][j]->GetType() == EPieceType::Knight && (i != endPos.first || j != endPos.second))
						return true;
		}


	return false;
}

bool Board::IsKingInCheck(const Position& currentPos, EPieceColor color) const
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && (m_board[i][j]->GetColor() != color) && m_board[i][j]->CanMove(Position(i, j), currentPos, true, *this))
				return true;
		}
	}
	return false;
}

// m_board[i][j]->GetType() != EPieceType::King && (m_board[i][j]->GetColor() != color)

bool Board::IsCheckmate(EPieceColor color) const
{
	Position kingPos;

	//search for king's position on board
	bool found = 0;
	for (int i = 0; i < 8 && found == 0; i++)
	{
		for (int j = 0; j < 8 && found == 0; j++)
		{
			if (m_board[i][j] && m_board[i][j]->Is(EPieceType::King, color))
			{
				kingPos.first = i;
				kingPos.second = j;
				found = 1;
			}
		}
	}

	//if king is in check -> verify if it is checkmate
	if (IsKingInCheck(kingPos, color))
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (m_board[i][j] && m_board[i][j]->GetColor() == color)
				{
					for (auto it : m_board[i][j]->GetPossibleMoves(Position(i, j), false, *this))
					{
						//if the king is not left in check, there is a possible move to be made to save the king
						if (m_board[i][j]->GetType() != EPieceType::King && !IsKingLeftInCheck(Position(i, j), it, color))
							return false;
						if (m_board[i][j]->GetType() == EPieceType::King)
							return false;
					}
				}
			}
		}
		return true;
	}
	return false;
}

bool Board::IsStaleMate(EPieceColor color) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j] && m_board[i][j]->GetColor() == color)
				if (!m_board[i][j]->GetPossibleMoves(Position(i, j), false, *this).empty())
					return false;
		}
	}

	return true;
}

static bool VerifyInsufficientMaterialVect(std::vector<bool> vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i] == false)
			return false;
		return true;
	}
}

bool Board::IsInsufficientMaterial() const
{
	std::vector<bool> twoKings = { false, false };
	std::vector<bool> twoKingsOneKnight = { false, false, false };
	std::vector<bool> twoKingsOneBishop = { false, false, false };
	std::vector<bool> twoKingsTwoBishops = { false, false, false, false };
	bool colorBishop;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_board[i][j])
			{
				auto type = m_board[i][j]->GetType();
				auto color = m_board[i][j]->GetColor();
				if (type == EPieceType::Queen || type == EPieceType::Rook)
					return false;
				if (type == EPieceType::King)
				{
					twoKings[(int)color] = true;
					twoKingsOneKnight[(int)color] = true;
					twoKingsOneBishop[(int)color] = true;
					twoKingsTwoBishops[(int)color] = true;
				}
				if (type == EPieceType::Knight)
				{
					if (twoKingsOneKnight[2] || twoKingsOneBishop[2])
						return false;
					else
						twoKingsOneKnight[2] = true;
				}
				if (type == EPieceType::Bishop)
				{
					// to be continued
					if (twoKingsOneKnight[2])
						return false;
					if (twoKingsOneBishop[2])
						if (colorBishop != ((i + j) % 2))
							return false;
						else
							twoKingsTwoBishops[3] = true;
					else
					{
						twoKingsOneBishop[2] = true;
						twoKingsTwoBishops[2] = true;
						colorBishop = (i + j) % 2;
					}
				}
			}

		}
	}

	return VerifyInsufficientMaterialVect(twoKings) || VerifyInsufficientMaterialVect(twoKingsOneKnight)
		|| VerifyInsufficientMaterialVect(twoKingsOneBishop) || VerifyInsufficientMaterialVect(twoKingsTwoBishops);
}

bool Board::IsThreefoldRepetitionDraw()
{
	std::bitset<256> currentBitBoard = GenerateBitset();
	m_bitBoards.push_back(currentBitBoard);
	int contor = 0;
	for (int it = 0; it < m_bitBoards.size(); it++)
	{
		if (m_bitBoards[it] == currentBitBoard)
			contor++;
	}
	if (contor == 3)
		return true;
	return false;
}

void Board::SetBitBoardsToEmpty()
{
	m_bitBoards.clear();
}

ConfigCastlingPossible Board::GetCastlingVect() const
{
	return CastlingPossible;
}