#include "Game.h"

Game::Game() 
	: m_turn(0)
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
	if (IsGameOver())
		return m_turn ? EPlayer::White : EPlayer::Black;

	//exception or draw
	return EPlayer::None;
}

bool Game::IsGameOver() const
{
	EPieceColor color = m_turn ? EPieceColor::Black : EPieceColor::White;
	
	return m_board.IsCheckmate(color);
}

static bool IsPositionValid(Position p)
{
	return p.first >= 1 && p.first <= 8 && p.second >= 1 && p.second <= 8;
}

bool Game::MakeMove(const std::string& startPosStr, const std::string& endPosStr)
{
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