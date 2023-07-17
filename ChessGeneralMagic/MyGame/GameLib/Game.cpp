#include "Game.h"

#include <iostream>

Game::Game()
{
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

//void Game::Play()
//{
//	std::cout << "Test";
//}

void Game::MakeMove(Position startPos, Position endPos)
{
	m_board.MakeMove(startPos, endPos);
}

IPieceInfoPtr Game::GetPieceInfo(int i, int j)
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

EPieceColor PieceInfo::GetColor()
{
	return m_color;
}

EPieceType PieceInfo::GetType()
{
	return m_type;
}
