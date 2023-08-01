
#include "Game.h"
#include "PieceInfo.h"

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
	, m_moves(1)
{}

Game::Game(int turn, EGameState state, ConfigMatrix m)
	: m_state(state)
	, m_turn(turn)
	, m_board(m)
	, m_moves(1)
{}

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

static char PieceTypeToChar(EPieceType type)
{
	std::string TYPES = "PRNBQK";
	return TYPES[(int)type];
}

void Game::UpdatePGN(Position startPos, Position endPos)
{
	if (m_turn)
		m_pgn += ' ';
	else
	{
		m_pgn += ' ';
		m_pgn += '0' + m_moves;
		m_pgn += ". ";
		m_moves++;
	}		

	//copy board
	Board board(m_board);
	//valid pos of the second rook or knight if it can move the same
	Position otherPiecePos = board.CanTheOtherPieceMove(startPos, endPos);

	// simulate the move to see if it can be done
	if (board.MakeMove(startPos, endPos))
	{
		auto piece = GetPieceInfo(startPos);
		auto endPosPiece = GetPieceInfo(endPos);

		if (piece->GetType() == EPieceType::King)
		{
			// symbol for castling
			if (startPos.second - endPos.second == 2)
			{
				m_pgn += "O-O-O";
				return;
			}
			if (startPos.second - endPos.second == -2)
			{
				m_pgn += "O-O";
				return;
			}
		}
		if (piece->GetType() != EPieceType::Pawn)
		{
			m_pgn += PieceTypeToChar(piece->GetType());
			if (piece->GetType() == EPieceType::Rook || piece->GetType() == EPieceType::Knight)
			{
				//verify if the second rook or knight can make the same move, add specifications
				if (otherPiecePos.first == startPos.first)
					m_pgn += 'a' + startPos.second;
				else if (otherPiecePos.second == startPos.second)
					m_pgn += '0' + (8 - startPos.first);
			}

			if (endPosPiece)
				m_pgn += 'x';
		}
		else
		{
			// pawn move representation
			if (endPosPiece)
			{
				m_pgn += 'a' + startPos.second;
				m_pgn += 'x';
			}
		}
		// end position representation
		m_pgn += 'a' + endPos.second;
		m_pgn +='0' + (8 - endPos.first);
	}

	auto colorUpdated = m_turn ? EPieceColor::White : EPieceColor::Black;
	Position kingPos = board.GetKingPos(colorUpdated);
	if (board.IsCheckmate(colorUpdated))
		m_pgn += '#';
	else if (board.IsKingInCheck(kingPos, colorUpdated))
		m_pgn += '+';
}

bool Game::CanUpgradePawn(Position pos) const
{
	return m_board.IsUpgradeablePawn(pos);
}

void Game::MakeMove(Position startPos, Position endPos)
{
	auto color = m_turn ? EPieceColor::Black : EPieceColor::White;

	if (!IsPositionValid(startPos) || !IsPositionValid(endPos))
		throw OutOfBoundException();

	if (!m_board.IsPieceColor(startPos, color))
		throw InvalidStartPositionExcepton();

	UpdatePGN(startPos, endPos);

	auto prevPossibleMoves = m_board.GetPossibleMoves(startPos);
	auto endPosPiece = GetPieceInfo(endPos);

	if (m_board.MakeMove(startPos, endPos))
		if (endPosPiece)
		{
			auto capturedColor = endPosPiece->GetColor();
			m_board.AddCapturedPiece(endPosPiece);
			NotifyCaptureMade(capturedColor, GetCapturedPieces(capturedColor));
		}

	if (CanUpgradePawn(endPos))
	{
		UpdateState(EGameState::WaitingForPawnUpgrade);
		NotifyPawnUpgrade();
	}
	else
	{
		m_turn = 1 - m_turn;
		NotifyMoveMade(startPos, endPos, prevPossibleMoves);
	}

	if (m_board.IsStaleMate(color) || m_board.IsThreefoldRepetitionDraw() || m_board.IsInsufficientMaterial())
	{
		UpdateState(EGameState::Draw);
		NotifyGameOver(EGameResult::Draw);
	}

	auto colorUpdated = m_turn ? EPieceColor::Black : EPieceColor::White;
	if (m_board.IsCheckmate(colorUpdated))
	{
		m_pgn += '#';
		m_pgn += "//WHOWON//"; //how won
		UpdateState(colorUpdated == EPieceColor::White ? EGameState::BlackWon : EGameState::WhiteWon);
		NotifyGameOver(colorUpdated == EPieceColor::White ? EGameResult::BlackWon : EGameResult::WhiteWon);
	}

}


void Game::ResetGame()
{
	m_turn = 0;
	UpdateState(EGameState::Playing);
	m_board.InitializeBoard();
	m_board.SetBitBoardsToEmpty();
}

void Game::NotifyMoveMade(Position startPos, Position endPos, PositionList prevPossibleMoves)
{
	for (auto it = m_observers.begin(); it != m_observers.end();)
	{
		if (auto sp = it->lock())
		{
			sp->OnMoveMade(startPos, endPos, prevPossibleMoves);
			++it;
		}
		else
			it = m_observers.erase(it);
	}
}

void Game::NotifyCaptureMade(EPieceColor color, IPieceInfoPtrList capturedPieces)
{
	for (auto it = m_observers.begin(); it != m_observers.end();)
	{
		if (auto sp = it->lock())
		{
			sp->OnCaptureMade(color, capturedPieces);
			++it;
		}
		else
			it = m_observers.erase(it);
	}
}

void Game::NotifyPawnUpgrade()
{
	for (auto it = m_observers.begin(); it != m_observers.end();)
	{
		if (auto sp = it->lock())
		{
			sp->OnPawnUpgrade();
			++it;
		}
		else
			it = m_observers.erase(it);
	}
}

void Game::NotifyGameOver(EGameResult result)
{
	for (auto it = m_observers.begin(); it != m_observers.end();)
	{
		if (auto sp = it->lock())
		{
			sp->OnGameOver(result);
			++it;
		}
		else
			it = m_observers.erase(it);
	}
}

void Game::InitializeGamePGN(ConfigPGN strPGN)
{
	
}

ConfigPGN Game::GetPGN()
{
	return m_pgn;
}

void Game::InitializeGameFEN(ConfigFEN strFEN)
{
	m_board.InitializeBoardFEN(strFEN);

	if (strFEN == "w")
		m_turn = 0;
	else
		m_turn = 1;
}

ConfigFEN Game::GenerateFEN()
{
	auto gameFENState = m_board.GenerateBoardFEN();

	gameFENState += m_turn ? 'b' : 'w';
	gameFENState += ' ';

	auto castlingPossibleFEN = m_board.GenerateCastlingPossibleFEN();

	gameFENState += castlingPossibleFEN;

	return gameFENState;
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

IPieceInfoPtrList Game::GetCapturedPieces(EPieceColor color) const
{
	return m_board.GetCapturedPieces(color);
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
	if (!IsState(EGameState::WaitingForPawnUpgrade))
		throw NotStateWaitingForPawnUpdate();

	auto color = m_turn ? EPieceColor::Black : EPieceColor::White;
	int i = m_turn ? 7 : 0;

	if (type == EPieceType::None || type == EPieceType::Pawn || type == EPieceType::King)
		throw InvalidUpgradeType();

	for (int j = 0; j < 7; j++)
	{
		if (GetPieceInfo({ i, j }) && GetPieceInfo({ i, j })->GetType() == EPieceType::Pawn)
			m_board.SetPiece({ i, j }, color, type);
	}

	// update PGN 
	m_pgn += '=' + PieceTypeToChar(type);

	m_turn = 1 - m_turn;
	UpdateState(EGameState::Playing);
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

IPieceInfoPtr Game::GetPieceInfo(Position pos) const
{
	return m_board.GetPieceInfo(pos);
}
