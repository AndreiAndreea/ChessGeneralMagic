#include "Game.h"

#include "ChessExceptions.h"
#include "OutOfBoundException.h"
#include "InvalidDrawResponseException.h"
#include "InvalidUpgradeType.h"
#include "InvalidStartPositionExcepton.h"
#include "NotStateDrawProposedException.h"
#include "NotStateWaitingForPawnUpdate.h"
#include "NotStatePlayingException.h"

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
	return p.first >= 0 && p.first < 8 && p.second >= 0 && p.second < 8;
}

static bool IsComandDraw(const std::string& comand)
{
	return comand == "DRAW";
}

static bool RefuseDraw(const std::string& comand)
{
	return comand == "NO DRAW";
}

bool Game::CanUpgradePawn(Position pos) const
{
	auto piece = m_board.GetBoard()[pos.first][pos.second];
	return piece->GetType() == EPieceType::Pawn && ((piece->GetColor() == EPieceColor::White && pos.first == 0) || (piece->GetColor() == EPieceColor::Black && pos.first == 7));
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
	NotifyOnMoveMade();

	if (CanUpgradePawn(endPos))
	{
		m_board.AddToMoves(startPos, endPos, color);
		UpdateState(EGameState::WaitingForPawnUpgrade);
		NotifyOnPawnUpgrade();
	}
	else
		m_turn = 1 - m_turn;

	if (m_board.IsStaleMate(color) || m_board.IsThreefoldRepetitionDraw() || m_board.IsInsufficientMaterial())
	{
		UpdateState(EGameState::Draw);
		NotifyOnGameOver();
	}

	auto colorUpdated = m_turn ? EPieceColor::Black : EPieceColor::White;
	if (m_board.IsCheckmate(colorUpdated))
	{
		UpdateState(colorUpdated == EPieceColor::White ? EGameState::BlackWon : EGameState::WhiteWon);
		NotifyOnGameOver();
	}

}


void Game::ResetGame()
{
	m_turn = 0;
	UpdateState(EGameState::Playing);
	m_board.InitializeBoard();
	m_board.SetBitBoardsToEmpty();
}

void Game::NotifyOnMoveMade()
{
	for (auto it : m_observers)
	{
		if (auto sp = it.lock())
			sp->OnMoveMade();
		else
		{
			auto itPtr = it.lock().get();
			RemoveListener(itPtr);
		}
	}
}

void Game::NotifyOnPawnUpgrade()
{
	for (auto it : m_observers)
	{
		if (auto sp = it.lock())
			sp->OnPawnUpgrade();
		else
		{
			auto itPtr = it.lock().get();
			RemoveListener(itPtr);
		}
	}
}

void Game::NotifyOnGameOver()
{
	for (auto it : m_observers)
	{
		if (auto sp = it.lock())
			sp->OnGameOver();
		else
		{
			auto itPtr = it.lock().get();
			RemoveListener(itPtr);
		}
	}
}

void Game::AddListener(IGameListenerPtr listener)
{
	m_observers.push_back(listener);
}

void Game::RemoveListener(IGameListener* listener)
{
	auto func = [listener](IGameListenerWeakPtr& weak)
	{
		auto sp = weak.lock();

		return !sp || sp.get() == listener;
			
	};

	m_observers.erase(std::remove_if(m_observers.begin(), m_observers.end(), func));

	/*for (auto it = m_observers.begin(); it != m_observers.end();)
	{
		if (auto sp = it->lock())
		{
			if (sp.get() == listener)
				it = m_observers.erase(it);
			else
				++it;
		}
		else
			it = m_observers.erase(it);
	}*/
}

PositionList Game::GetPossibleMoves(Position pos)
{
	return m_board.GetPossibleMoves(pos);
}

bool Game::IsPlaying() const
{
	return m_state == EGameState::Playing;
}

void Game::PlayerDrawComand(EDrawComand respons)
{
	switch (respons)
	{
	case EDrawComand::Draw:
		if (!IsState(EGameState::Playing))
			throw NotStatePlayingException();
		UpdateState(EGameState::DrawProposed);
		m_turn = 1 - m_turn;
		break;
	case EDrawComand::Accept:
		if (!IsState(EGameState::DrawProposed))
			throw NotStateDrawProposedException();
		UpdateState(EGameState::Draw);
		break;
	case EDrawComand::Decline:
		if (!IsState(EGameState::DrawProposed))
			throw NotStateDrawProposedException();
		UpdateState(EGameState::Playing);
		m_turn = 1 - m_turn;
		break;
	}
}

void Game::UpgradePawnTo(EPieceType type)
{
	auto ceva = m_state;
	if (!IsState(EGameState::WaitingForPawnUpgrade))
		throw NotStateWaitingForPawnUpdate();

	auto color = m_turn ? EPieceColor::Black : EPieceColor::White;

	if (type != EPieceType::None)
	{
		auto movesVect = m_board.GetMovesVect();
		m_board.SetPiece(movesVect[(int)color][movesVect[(int)color].size() - 1].second, color, type);
		m_turn = 1 - m_turn;
		UpdateState(EGameState::Playing);
	}
	else
		throw InvalidUpgradeType();
}

bool Game::IsWaitingForPawnUpgrade() const
{
	return m_state == EGameState::WaitingForPawnUpgrade;
}

bool Game::IsDrawProposed() const
{
	return m_state == EGameState::DrawProposed;
}

bool Game::IsDraw() const
{
	return m_state == EGameState::Draw;
}

EPieceColor Game::GetCurrentPlayer() const
{
	return m_turn ? EPieceColor::Black : EPieceColor::White;
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
	return Position(8 - (pos[1] - '0'), pos[0] - 'A');
}


IPieceInfoPtr Game::GetPieceInfo(Position pos) const
{
	//return m_board->GetPieceInfo(i, j);

	if (auto piece = m_board.GetBoard()[pos.first][pos.second])
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