#include "Game.h"

Game::Game()
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
	return EPlayer();
}

bool Game::IsGameOver() const
{
	return false;
}

void Game::MakeMove(Position startPos, Position endPos)
{
	m_board.MakeMove(startPos, endPos);
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