
#include "Board.h"
#include "PieceInfo.h"

#include "KingLeftInCheckException.h"
#include "InvalidMovingPatternException.h"

#include <cstring>

Board::Board()
{
	InitializeBoard();
}

static EPieceType GetType(char c)
{
	static const EPieceType TYPES[] = { EPieceType::Pawn, EPieceType::Rook, EPieceType::Knight, EPieceType::Bishop, EPieceType::Queen, EPieceType::King };
	c = toupper(c);
	static char str[] = "PRNBQK";
	char* p = strchr(str, c);
	return TYPES[p - str];
}

Board::Board(ConfigMatrix board)
{
	m_pieceMatrix.resize(8);
	for (int i = 0; i < 8; i++)
	{
		m_pieceMatrix[i].resize(8);
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != '-')
			{
				EPieceType type = GetType(board[i][j]);
				EPieceColor color = board[i][j] > 91 ? EPieceColor::White : EPieceColor::Black;

				m_pieceMatrix[i][j] = Piece::Produce(type, color);
			}
			else
				m_pieceMatrix[i][j] = nullptr;
		}
	}
	m_bitBoards.clear();
	m_bitBoards.push_back(GenerateBitset());
}

static char PieceInfoToChar(EPieceType type, EPieceColor color)
{
	static std::string letters = "prnbqk";
	char c = letters[(int)type];
	return color == EPieceColor::White ? toupper(c) : c;
}

Board::Board(int)
{
	m_pieceMatrix.resize(8);
	for (int x = 0; x < 8; x++)
	{
		m_pieceMatrix[x].resize(8);
		for (int y = 0; y < 8; y++)
			m_pieceMatrix[x][y] = nullptr;
	}
}

Board::Board(const Board& ob)
{
	m_pieceMatrix = ob.GetBoard();
	m_castlingPossible = ob.GetCastlingVect();
	m_capturedPieces[0] = ob.GetCapturedPieces(EPieceColor::White);
	m_capturedPieces[1] = ob.GetCapturedPieces(EPieceColor::Black);
}

void Board::InitializeBoardFEN(ConfigFEN& strFEN)
{
	// pieces on board
	for (int i = 0; i < 8 && strFEN[0] != ' '; i++)
	{
		for (int j = 0; j < 8 && strFEN[0] != ' '; j++)
		{
			if (isdigit(strFEN[0]))
			{
				int digit = strFEN[0] - '0';
				while (digit)
				{
					m_pieceMatrix[i][j++] = nullptr;
					digit--;
				}
				j--;
			}
			else if (strFEN[0] != '/')
			{
				EPieceColor color = strFEN[0] < 91 ? EPieceColor::White : EPieceColor::Black;
				EPieceType type = GetType(strFEN[0]);

				m_pieceMatrix[i][j] = Piece::Produce(type, color);
			}
			strFEN.erase(strFEN.begin());
		}
		strFEN.erase(strFEN.begin());
	}


	// castling possibility
	m_castlingPossible = { {false, false}, {false, false} };

	int i;
	for (i = strFEN.size() - 1; i > strFEN.size() - 5; i--)
	{
		if (strFEN[i] = 'q')
			m_castlingPossible[1][0] = true;
		if (strFEN[i] = 'k')
			m_castlingPossible[1][1] = true;
		if (strFEN[i] = 'Q')
			m_castlingPossible[0][0] = true;
		if (strFEN[i] = 'K')
			m_castlingPossible[0][1] = true;
		strFEN.erase(strFEN.begin() + i);
	}
	strFEN.erase(strFEN.begin() + i);

	// captured pieces
	m_capturedPieces = { {}, {} };
}

void Board::InitializeBoard()
{
	m_pieceMatrix.resize(8);
	for (int i = 0; i < 8; i++)
		m_pieceMatrix[i].resize(8);

	// initializing the empty spaces on the board

	for (int x = 2; x < 6; x++)
		for (int y = 0; y < 8; y++)
			m_pieceMatrix[x][y] = nullptr;

	//initializing the pieces 

	std::vector<EPieceType> TYPES = { EPieceType::Rook, EPieceType::Knight, EPieceType::Bishop, EPieceType::Queen, EPieceType::King, EPieceType::Bishop, EPieceType::Knight, EPieceType::Rook };

	for (int i = 0; i < 8; i++)
	{
		m_pieceMatrix[0][i] = Piece::Produce(TYPES[i], EPieceColor::Black);
		m_pieceMatrix[7][i] = Piece::Produce(TYPES[i], EPieceColor::White);
	}

	for (int i = 0; i < 8; i++)
	{
		m_pieceMatrix[1][i] = Piece::Produce(EPieceType::Pawn, EPieceColor::Black);
		m_pieceMatrix[6][i] = Piece::Produce(EPieceType::Pawn, EPieceColor::White);
	}
}

PieceMatrix Board::GetBoard() const
{
	return m_pieceMatrix;
}

PositionList Board::GetPossibleMoves(Position pos) const
{
	if (m_pieceMatrix[pos.first][pos.second])
		return m_pieceMatrix[pos.first][pos.second]->GetPossibleMoves(pos, false, *this);
	return {};
}

IPieceInfoPtrList Board::GetCapturedPieces(EPieceColor color) const
{
	return m_capturedPieces[(int)color];
}

IPieceInfoPtr Board::GetPieceInfo(Position pos) const
{
	if (auto piece = m_pieceMatrix[pos.first][pos.second])
		return std::make_shared<PieceInfo>(piece->GetType(), piece->GetColor());
	return {};
}

ConfigFEN Board::GenerateBoardFEN()
{
	ConfigFEN boardStateFEN;

	for (int i = 0; i < 8; i++)
	{
		int emptyCells = 0;

		for (int j = 0; j < 8; j++)
		{
			if (m_pieceMatrix[i][j])
			{
				if (emptyCells > 0)
				{
					boardStateFEN += '0' + emptyCells;
					emptyCells = 0;
				}
				boardStateFEN += PieceInfoToChar(m_pieceMatrix[i][j]->GetType(), m_pieceMatrix[i][j]->GetColor());
			}
			else
				emptyCells++;
		}
		if (emptyCells > 0)
			boardStateFEN += '0' + emptyCells;

		if (i != 7)
			boardStateFEN += '/';
	}

	boardStateFEN += ' ';
	return boardStateFEN;
}

ConfigFEN Board::GenerateCastlingPossibleFEN()
{
	ConfigFEN castlingPossibleFEN;

	castlingPossibleFEN += m_castlingPossible[0][0] ? 'Q' : '-';
	castlingPossibleFEN += m_castlingPossible[0][1] ? 'K' : '-';
	castlingPossibleFEN += m_castlingPossible[1][0] ? 'q' : '-';
	castlingPossibleFEN += m_castlingPossible[1][1] ? 'k' : '-';

	return castlingPossibleFEN;
}

void Board::SetPiece(const Position& pos, EPieceColor color, EPieceType type)
{
	m_pieceMatrix[pos.first][pos.second] = Piece::Produce(type, color);
}

void Board::SetPieceToNullptr(const Position& pos)
{
	m_pieceMatrix[pos.first][pos.second] = nullptr;
}

void Board::MoveRookForCastling(int castlingType, EPieceColor color)
{
	int i = (int)color ? 0 : 7;
	int start = castlingType < 0 ? 7 : 0;
	int end = castlingType < 0 ? 5 : 3;

	SetPiece(Position(i, end), color, EPieceType::Rook);
	SetPieceToNullptr(Position(i, start));
}

BoardConfig Board::GenerateBitset()
{
	int k = 0;
	std::bitset<256> currentBitBoard;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_pieceMatrix[i][j])
			{
				auto color = (int)m_pieceMatrix[i][j]->GetColor();
				auto type = (int)m_pieceMatrix[i][j]->GetType();

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
	auto piece = m_pieceMatrix[startPos.first][startPos.second];
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

		// CASTLING
		if (type == EPieceType::King)
		{
			if (abs(startPos.second - endPos.second) == 2)
				MoveRookForCastling(startPos.second - endPos.second, color);

			//king move for castling
			m_castlingPossible[(int)color] = { false, false };
		}

		if (type == EPieceType::Rook)
		{
			if (startPos.second == 0)
				m_castlingPossible[(int)color][0] = false;
			if (startPos.second == 7)
				m_castlingPossible[(int)color][1] = false;
		}

		return true;
	}
	throw InvalidMovingPatternException();
}

bool Board::IsPieceColor(Position pos, EPieceColor color) const
{
	auto piece = m_pieceMatrix[pos.first][pos.second];

	return piece && piece->GetColor() == color;
}

bool Board::IsPieceColorType(Position pos, EPieceColor color, EPieceType type) const
{
	auto piece = m_pieceMatrix[pos.first][pos.second];
	return piece && piece->Is(type, color);
}

static bool IsOpposite(PiecePtr piece, EPieceColor color, std::vector<EPieceType> types)
{
	return piece && piece->IsOpposite(color, { EPieceType::Bishop, EPieceType::Queen });
}

Position Board::GetKingPos(EPieceColor color) const
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (m_pieceMatrix[i][j] && m_pieceMatrix[i][j]->Is(EPieceType::King, color))
				return Position(i, j);
	return Position(-1, -1);
}

Position Board::FindPieceStartPos(int startRow, int startCol, Position endPos, EPieceType type, EPieceColor color)
{
	if (startRow != -1)
		for (int i = 0; i < 8; i++)
		{
			auto piece = m_pieceMatrix[startRow][i];
			if (piece && piece->Is(type, color) && piece->CanMove({ startRow, i }, endPos, false, *this))
				return { startRow, i };
		}
	else if (startCol != -1)
		for (int i = 0; i < 8; i++)
		{
			auto piece = m_pieceMatrix[i][startCol];
			if (piece && piece->Is(type, color) && piece->CanMove({ i, startCol }, endPos, false, *this))
				return { i, startCol };
		}
	else
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				auto piece = m_pieceMatrix[i][j];
				if (piece && piece->Is(type, color) && piece->CanMove({ i, j }, endPos, false, *this))
					return { i, j };
			}
		}
}

Position Board::CanTheOtherPieceMove(Position startPos, Position endPos)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			auto initialPiece = m_pieceMatrix[startPos.first][startPos.second];
			auto currentPiece = m_pieceMatrix[i][j];

			if (currentPiece && Position(i, j) != startPos && currentPiece->Is(initialPiece->GetType(), initialPiece->GetColor())
				&& currentPiece->CanMove({ i, j }, endPos, false, *this))
			{
				return { i,j };
			}
		}
	}

	return { -1,-1 };
}

bool Board::CheckingRookThreat(const Position& kingPos, const Position& startPos, const Position& endPos, int i, int j, std::bitset<2> direction)
{
	auto pieceColor = m_pieceMatrix[kingPos.first][kingPos.second]->GetColor();
	auto directionStr = direction.to_string();
	int rowIncrement, columnIncrement, limit;
	std::vector<EPieceType> TYPES = { EPieceType::Queen, EPieceType::Rook };

	if (directionStr[0])
	{
		rowIncrement = 0;
		columnIncrement = directionStr[1] ? -1 : +1;
	}
	else
	{
		columnIncrement = 0;
		rowIncrement = directionStr[1] ? -1 : +1;
	}

	limit = directionStr[1] ? 0 : 7;

	while ((i != 8 || i != -1) && (j != 8 || j != -1))
	{
		if (i == endPos.first && j == endPos.second)
			break;
		auto piece = m_pieceMatrix[i][j];
		if (!(i == startPos.first && j == startPos.second))
			if (piece)
			{
				if (IsOpposite(piece, pieceColor, TYPES))
					return true;
				break;
			}
		i += rowIncrement;
		j += columnIncrement;
	}
}

bool Board::IsKingLeftInCheck(const Position& startPos, const Position& endPos, EPieceColor pieceColor) const
{
	Position kingPos = GetKingPos(pieceColor);

	if (kingPos.second == -1)
		auto ceva = 1;

	//checking Rook
	int i = kingPos.first + 1;
	while (i < 8)
	{
		if (i == endPos.first && kingPos.second == endPos.second)
			break;
		auto piece = m_pieceMatrix[i][kingPos.second];
		if (!(i == startPos.first && kingPos.second == startPos.second))
			if (piece)
			{
				if (piece->GetColor() != pieceColor && (piece->GetType() == EPieceType::Rook || piece->GetType() == EPieceType::Queen))
					return true;
				break;
			}
		i++;
	}

	//std::bitset<2> direction(0);
	//CheckingRookThreat(kingPos, startPos, endPos, kingPos.first + 1, kingPos.second, direction);
	//std::bitset<2> direction(1);

	i = kingPos.first - 1;
	while (i >= 0)
	{

		if (i == endPos.first && kingPos.second == endPos.second)
			break;
		if (!(i == startPos.first && kingPos.second == startPos.second))
			if (m_pieceMatrix[i][kingPos.second] != nullptr)
			{
				if (m_pieceMatrix[i][kingPos.second]->GetColor() != pieceColor && (m_pieceMatrix[i][kingPos.second]->GetType() == EPieceType::Rook || m_pieceMatrix[i][kingPos.second]->GetType() == EPieceType::Queen))
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
			if (m_pieceMatrix[kingPos.first][i] != nullptr)
			{
				if (m_pieceMatrix[kingPos.first][i]->GetColor() != pieceColor && (m_pieceMatrix[kingPos.first][i]->GetType() == EPieceType::Rook || m_pieceMatrix[kingPos.first][i]->GetType() == EPieceType::Queen))
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
			if (m_pieceMatrix[kingPos.first][i] != nullptr)
			{
				if (m_pieceMatrix[kingPos.first][i]->GetColor() != pieceColor && (m_pieceMatrix[kingPos.first][i]->GetType() == EPieceType::Rook || m_pieceMatrix[kingPos.first][i]->GetType() == EPieceType::Queen))
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

		auto piece = m_pieceMatrix[currentRow][currentCol];
		if (!(currentRow == startPos.first && currentCol == startPos.second))
			//if (IsOpposite(piece, pieceColor, { EPieceType::Bishop, EPieceType::Queen }))
			if (m_pieceMatrix[currentRow][currentCol] != nullptr)
				if (m_pieceMatrix[currentRow][currentCol]->GetColor() != pieceColor && (m_pieceMatrix[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_pieceMatrix[currentRow][currentCol]->GetType() == EPieceType::Queen))
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
			if (m_pieceMatrix[currentRow][currentCol] != nullptr)
				if (m_pieceMatrix[currentRow][currentCol]->GetColor() != pieceColor && (m_pieceMatrix[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_pieceMatrix[currentRow][currentCol]->GetType() == EPieceType::Queen))
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
			if (m_pieceMatrix[currentRow][currentCol] != nullptr)
				if (m_pieceMatrix[currentRow][currentCol]->GetColor() != pieceColor && (m_pieceMatrix[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_pieceMatrix[currentRow][currentCol]->GetType() == EPieceType::Queen))
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
			if (m_pieceMatrix[currentRow][currentCol] != nullptr)
				if (m_pieceMatrix[currentRow][currentCol]->GetColor() != pieceColor && (m_pieceMatrix[currentRow][currentCol]->GetType() == EPieceType::Bishop || m_pieceMatrix[currentRow][currentCol]->GetType() == EPieceType::Queen))
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
			if (kingPos.second - 1 >= 0 && m_pieceMatrix[kingPos.first + 1][kingPos.second - 1] != nullptr && m_pieceMatrix[kingPos.first + 1][kingPos.second - 1]->GetColor() != pieceColor
				&& (kingPos.first + 1 != endPos.first || kingPos.second - 1 != endPos.second) && m_pieceMatrix[kingPos.first + 1][kingPos.second - 1]->GetType() == EPieceType::Pawn)
				return true;

			if (kingPos.second + 1 < 8 && m_pieceMatrix[kingPos.first + 1][kingPos.second + 1] != nullptr && m_pieceMatrix[kingPos.first + 1][kingPos.second + 1]->GetColor() != pieceColor
				&& (kingPos.first + 1 != endPos.first || kingPos.second + 1 != endPos.second) && m_pieceMatrix[kingPos.first + 1][kingPos.second + 1]->GetType() == EPieceType::Pawn)
				return true;
		}
	}

	if (pieceColor == EPieceColor::White)
	{
		if (kingPos.first - 1 >= 0)
		{
			if (kingPos.second - 1 >= 0 && m_pieceMatrix[kingPos.first - 1][kingPos.second - 1] != nullptr && m_pieceMatrix[kingPos.first - 1][kingPos.second - 1]->GetColor() != pieceColor
				&& (kingPos.first - 1 != endPos.first || kingPos.second - 1 != endPos.second) && m_pieceMatrix[kingPos.first - 1][kingPos.second - 1]->GetType() == EPieceType::Pawn)
				return true;

			if (kingPos.second + 1 < 8 && m_pieceMatrix[kingPos.first - 1][kingPos.second + 1] != nullptr && m_pieceMatrix[kingPos.first - 1][kingPos.second + 1]->GetColor() != pieceColor
				&& (kingPos.first - 1 != endPos.first || kingPos.second + 1 != endPos.second) && m_pieceMatrix[kingPos.first - 1][kingPos.second + 1]->GetType() == EPieceType::Pawn)
				return true;
		}
	}

	//check knight threat
	for (int i = kingPos.first - 2; i <= kingPos.first + 2; i++)
		for (int j = kingPos.second - 2; j <= kingPos.second + 2; j++)
		{
			if (i < 8 && i >= 0 && j < 8 && j >= 0)
				if (abs(kingPos.first - i) == 2 && abs(kingPos.second - j) == 1 || abs(kingPos.first - i) == 1 && abs(kingPos.second - j) == 2)
					if (m_pieceMatrix[i][j] != nullptr && m_pieceMatrix[i][j]->GetColor() != pieceColor && m_pieceMatrix[i][j]->GetType() == EPieceType::Knight && (i != endPos.first || j != endPos.second))
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
			if (m_pieceMatrix[i][j] && (!m_pieceMatrix[i][j]->Is(color)) && m_pieceMatrix[i][j]->CanMove(Position(i, j), currentPos, true, *this))
				return true;
		}
	}
	return false;
}

bool Board::IsCheckmate(EPieceColor color) const
{
	Position kingPos = GetKingPos(color);

	//if king is in check -> verify if it is checkmate
	if (!IsKingInCheck(kingPos, color))
		return false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			auto currPiece = m_pieceMatrix[i][j];

			if (currPiece && currPiece->Is(color))
			{
				for (auto it : currPiece->GetPossibleMoves(Position(i, j), false, *this))
				{
					//if the king is not left in check, there is a possible move to be made to save the king
					if (!currPiece->Is(EPieceType::King) && !IsKingLeftInCheck(Position(i, j), it, color))
						return false;
					if (currPiece->Is(EPieceType::King))
						return false;
				}
			}
		}
	}

	return true;
}

bool Board::IsStaleMate(EPieceColor color) const
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_pieceMatrix[i][j] && m_pieceMatrix[i][j]->Is(color))
				if (!m_pieceMatrix[i][j]->GetPossibleMoves(Position(i, j), false, *this).empty())
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
	}
	return true;
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
			if (m_pieceMatrix[i][j])
			{
				auto type = m_pieceMatrix[i][j]->GetType();
				auto color = m_pieceMatrix[i][j]->GetColor();
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
	BoardConfig currentBitBoard = GenerateBitset();
	m_bitBoards.push_back(currentBitBoard);

	return std::count(m_bitBoards.begin(), m_bitBoards.end(), currentBitBoard) >= 3;
}

bool Board::IsUpgradeablePawn(Position pos) const
{
	auto piece = m_pieceMatrix[pos.first][pos.second];
	return piece->GetType() == EPieceType::Pawn && ((piece->GetColor() == EPieceColor::White && pos.first == 0)
		|| (piece->GetColor() == EPieceColor::Black && pos.first == 7));
}

void Board::ResetBoard()
{
	InitializeBoard();
	m_castlingPossible = { {true, true}, {true, true} };
	m_capturedPieces = { {}, {} };
	SetBitBoardsToEmpty();
}

void Board::SetBitBoardsToEmpty()
{
	m_bitBoards.clear();
}

void Board::AddCapturedPiece(IPieceInfoPtr piece)
{
	m_capturedPieces[(int)piece->GetColor()].push_back(piece);
}

void Board::RemoveLastCapturedPiece(EPieceColor color)
{
	m_capturedPieces[(int)color].pop_back();
}

ConfigCastlingPossible Board::GetCastlingVect() const
{
	return m_castlingPossible;
}