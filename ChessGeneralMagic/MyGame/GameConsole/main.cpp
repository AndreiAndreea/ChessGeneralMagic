#include<iostream>

#include "IGame.h"

std::string PieceToStr(IPieceInfoPtr pieceInfo)
{
	std::string result;

	switch (pieceInfo->GetType())
	{
	case EPieceType::Rook:
		result = "R";
		break;
	case EPieceType::Bishop:
		result = "B";
		break;
	case EPieceType::Knight:
		result = "Kn";
		break;
	case EPieceType::King:
		result = "Ki";
		break;
	case EPieceType::Queen:
		result = "Q";
		break;
	case EPieceType::Pawn:
		result = "P";
		break;
	}
	if (pieceInfo->GetColor() == EPieceColor::White)
		result += "w";
	else
		result += "b";
	return result;
}

void PrintBoard( const IGame& game)
{
	auto board = game.GetBoard();
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (board.GetBoard()[i][j])
			{
				IPieceInfoPtr piece = std::make_shared<PieceInfo>(board.GetBoard()[i][j]->GetType(), board.GetBoard()[i][j]->GetColor());
				std::cout << PieceToStr(piece) << " ";
			}
			else
				std::cout << "0 ";
		}
		std::cout << "\n";
	}
}

int main()
{
	IGamePtr game = IGame::Produce();
	PrintBoard(game);
	//game.MakeMove(Position(2, 2), Position(3, 2));
	/*std::cout << "\n\n\n";
	PrintBoard(game);*/
	return 0;
}