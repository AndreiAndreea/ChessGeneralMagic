#include "Game.h"

Game::Game()
	: m_turn(0)
	, state(EGameState::Playing)
	, m_proposeDraw(false)
	, m_draw(false)
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
	if (state == EGameState::BlackWon)
		return EPlayer::Black;
	if (state == EGameState::WhiteWon)
		return EPlayer::White;

	return EPlayer::None;
}

bool Game::IsGameOver() const
{
	return state == EGameState::WhiteWon || state == EGameState::BlackWon || state == EGameState::Draw;
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

bool Game::MakeMove(const std::string& comand)
{
	if (state == EGameState::DrawProposed)
	{
		if (IsComandDraw(comand))
		{
			state = EGameState::Draw;
			return true;
		}
		else if (RefuseDraw(comand))
		{
			state = EGameState::Playing;
			m_turn = 1 - m_turn;
		}
		else
			return false;
	}

	if (state == EGameState::Playing)
	{
		if (IsComandDraw(comand))
		{
			state = EGameState::DrawProposed;
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

			if (!IsPositionValid(startPos) || !IsPositionValid(endPos))
				return false;

			auto color = m_turn ? EPieceColor::Black : EPieceColor::White;

			if (!m_board.IsPieceColor(startPos, color))
				return false;

			if (m_board.MakeMove(startPos, endPos))
			{
				m_turn = 1 - m_turn;
				return true;
			}

			return false;
		}
	}
}

bool Game::IsDraw() const
{
	return m_draw;
}

EPlayer Game::GetCurrentPlayer() const
{
	return m_turn ? EPlayer::Black : EPlayer::White;
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