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

void PrintBoard( const IGamePtr& game)
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			auto pieceInfo = game->GetPieceInfo(i, j);
			if (pieceInfo)
				std::cout << PieceToStr(pieceInfo) << " ";
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
	game->MakeMove("B7","B6");
	std::cout << "\n\n\n";
	PrintBoard(game);
	return 0;
}