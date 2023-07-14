#include "Game.h"

Board Game::GetBoard()
{
	return m_board;
}

void Game::Play()
{
	std::cout << "Test";
}

void Game::MakeMove(Position startPos, Position endPos, Board& board)
{
	auto piece = board.GetBoard()[startPos.first][startPos.second];
	if (piece->CanMove(startPos, endPos, board))
	{
		if (piece->GetType() != EPieceType::King)
			if (board.IsKingInCheck(startPos, endPos, piece->GetColor()))
			{
				std::cout << "Regele e in sah! Nu se poate face mutarea.";
				//throw
			}
		board.SetPiece(endPos, piece->GetColor(), piece->GetType());
		board.GetBoard()[startPos.first][startPos.second] = nullptr;
	}
}
