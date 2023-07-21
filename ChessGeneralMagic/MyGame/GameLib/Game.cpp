#include "Game.h"

Game::Game()
	: m_turn(0)
	, m_state(EGameState::Playing)
{
}

IGamePtr IGame::Produce()
{
	return std::make_shared<Game>();
}


Board Game::GetBoard() const
{
	return m_board;
}

EPlayer Game::GetWinner() const
{
	if (m_state == EGameState::BlackWon)
		return EPlayer::Black;
	if (m_state == EGameState::WhiteWon)
		return EPlayer::White;

	return EPlayer::None;
}

bool Game::IsGameOver() const
{
	return m_state == EGameState::WhiteWon || m_state == EGameState::BlackWon || m_state == EGameState::Draw;
}

static bool IsPositionValid(Position p)
{
	return p.first >= 1 && p.first <= 8 && p.second >= 1 && p.second <= 8;
}

bool IsComandDraw(std::string comand)
{
	return comand == "DRAW";
}

bool RefuseDraw(std::string comand)
{
	return comand == "NO DRAW";
}

bool Game::CanUpgradePawn(Position pos) const
{
	auto piece = m_board.GetBoard()[pos.first][pos.second];
	return piece->GetType() == EPieceType::Pawn && piece->GetColor() == EPieceColor::White && pos.first == 1 || piece->GetColor() == EPieceColor::Black && pos.first == 8;
}

EPieceType ConvertToType(std::string comand)
{
	if (comand == "ROOK")
		return EPieceType::Rook;
	if (comand == "KNIGHT")
		return EPieceType::Knight;
	if (comand == "BISHOP")
		return EPieceType::Bishop;
	if (comand == "QUEEN")
		return EPieceType::Queen;
	return EPieceType::None;
}

void Game::MakeMove(Position startPos, Position endPos)
{
	auto color = m_turn ? EPieceColor::Black : EPieceColor::White;

	if (!IsPositionValid(startPos) || !IsPositionValid(endPos))
		throw OutOfBoundException();

	if (!m_board.IsPieceColor(startPos, color))
		throw InvalidStartPositionExcepton();

	m_board.MakeMove(startPos, endPos);

	if (CanUpgradePawn(endPos))
	{
		m_board.AddToMoves(startPos, endPos, color);
		UpdateState(EGameState::WaitingForPawnUpgrade);
	}
	else
		m_turn = 1 - m_turn;

	if (m_board.IsStaleMate(color) || m_board.IsThreefoldRepetitionDraw(color))
		UpdateState(EGameState::Draw);

	if (m_board.IsCheckmate(color))
		UpdateState(color == EPieceColor::White ? EGameState::WhiteWon : EGameState::BlackWon);

}


std::vector<Position> Game::GetPossibleMoves(int i, int j)
{
	return m_board.GetPossibleMoves(i, j);
}

bool Game::IsStatePlaying() const
{
	return m_state == EGameState::Playing;
}

void Game::PlayerComand(const std::string& comand)
{
	if (IsState(EGameState::Playing))
	{
		if (IsComandDraw(comand))
		{
			UpdateState(EGameState::DrawProposed);
			m_turn = 1 - m_turn;
		}
		else
		{
			std::string startPosStr, endPosStr;
			startPosStr = comand.substr(0, 2);
			auto found = comand.find(" ");
			endPosStr = comand.substr(found + 1, 2);

			Position startPos = ConvertToPos(startPosStr);
			Position endPos = ConvertToPos(endPosStr);

			MakeMove(startPos, endPos);
		}
	}
	else
		throw NotStatePlayingException();
}

void Game::DrawReaponse(const std::string& respons)
{
	if (IsState(EGameState::DrawProposed))
	{
		if (IsComandDraw(respons))
		{
			UpdateState(EGameState::Draw);
		}
		else if (RefuseDraw(respons))
		{
			UpdateState(EGameState::Playing);
			m_turn = 1 - m_turn;
		}
		else
			throw InvalidDrawResponseException();
	}
	else
		throw NotStateDrawProposedException();
}

void Game::UpgradePawnTo(const std::string& typeUpgrade)
{

	if (IsState(EGameState::WaitingForPawnUpgrade))
	{
		auto color = m_turn ? EPieceColor::Black : EPieceColor::White;
		EPieceType type = ConvertToType(typeUpgrade);

		if (type != EPieceType::None)
		{
			auto movesVect = m_board.GetMovesVect();
			m_board.SetPiece(movesVect[(int)color][movesVect[(int)color].size() - 1].second, color, type);
		}
		else
			throw InvalidUpgradeType();
	}
	else
		throw NotStateWaitingForPawnUpdate();
}

bool Game::IsStateWaitingForPawnUpgrade() const
{
	return m_state == EGameState::WaitingForPawnUpgrade;
}

bool Game::IsStateDrawProposed() const
{
	return m_state == EGameState::DrawProposed;
}

bool Game::IsStateDraw() const
{
	return m_state == EGameState::Draw;
}

EPlayer Game::GetCurrentPlayer() const
{
	return m_turn ? EPlayer::Black : EPlayer::White;
}

bool Game::IsState(EGameState state) const
{
	return m_state == state;
}

void Game::UpdateState(EGameState state)
{
	m_state = state;
}

Position Game::ConvertToPos(const std::string& pos)
{
	return Position(9 - (pos[1] - '0'), pos[0] - 'A' + 1);
}


IPieceInfoPtr Game::GetPieceInfo(int i, int j) const
{
	if (auto piece = m_board.GetBoard()[i][j])
		return std::make_shared<PieceInfo>(piece->GetType(), piece->GetColor());
	return {};
}

PieceInfo::PieceInfo(EPieceType type, EPieceColor color)
	: m_type(type)
	, m_color(color)
{

}

EPieceColor PieceInfo::GetColor() const
{
	return m_color;
}

EPieceType PieceInfo::GetType() const
{
	return m_type;
}