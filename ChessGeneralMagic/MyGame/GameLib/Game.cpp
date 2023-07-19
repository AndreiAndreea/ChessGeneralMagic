#include "Game.h"

Game::Game() : m_turn(0)
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

void Game::Play()
{

}

EPlayer Game::GetWinner() const
{
	if (IsGameOver())
	{
		if (m_turn)
			return EPlayer::White;
		return EPlayer::Black;
	}
	//exception or 
	return EPlayer::None;
}

bool Game::IsGameOver() const
{
	EPieceColor color;
	if (m_turn)
		color = EPieceColor::Black;
	else
		color = EPieceColor::White;
	if (m_board.IsCheckmate(color))
		return true;
	return false;
}

bool Game::MakeMove(const std::string& startPosStr, const std::string& endPosStr)
{
	Position startPos = ConvertToPos(startPosStr);
	Position endPos = ConvertToPos(endPosStr);

	if (IsInputValid(startPos, endPos) && m_board.MakeMove(startPos, endPos))
	{
		m_turn = 1 - m_turn;
		return true;
	}
	return false;

}

EPlayer Game::GetCurrentPlayer() const
{
	if(m_turn)
		return EPlayer::Black;
	return EPlayer::White;
		
}

Position Game::ConvertToPos(const std::string& pos)
{
	Position convertedPos;
	convertedPos.second = pos[0] - 'A' + 1;
	convertedPos.first = 9 - (pos[1] - '0');
	return convertedPos;
}

bool Game::IsInputValid(const Position& startPos, const Position& endPos)
{
	if (startPos.first < 1 || startPos.first > 8 || startPos.second < 1 || startPos.second > 8)
		return false;
	if (m_board.GetBoard()[startPos.first][startPos.second])
		if (m_turn)
		{
			if (m_board.GetBoard()[startPos.first][startPos.second]->GetColor() != EPieceColor::Black)
				return false;
		}
		else
		{
			if (m_board.GetBoard()[startPos.first][startPos.second]->GetColor() != EPieceColor::White)
				return false;
		}

	if (endPos.first < 1 || endPos.first > 8 || endPos.second < 1 || endPos.second > 8)
		return false;
		
	return true;
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