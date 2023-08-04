#include "PGNBuilder.h"
#include <fstream>

PGNBuilder::PGNBuilder()
{
}

PGNBuilder::PGNBuilder(const std::string& playerWhite, const std::string& playerBlack, const std::string& location)
	: m_playerWhite(playerWhite)
	, m_playerBlack(playerBlack)
	, m_location(location)
{
	m_result = "*"; // Default result as "*" (unfinished game)
}

const std::string& PGNBuilder::GetInfoPGN(EInfoPGN infoType) const
{
	std::vector<std::string> InfoVect = { m_playerWhite, m_playerBlack, m_location, m_result };
	return InfoVect[(int)infoType];
}

const std::vector<std::string> PGNBuilder::GetMoves() const
{
	return m_moves;
}

void PGNBuilder::AddMove(const std::string& move)
{
	m_moves.push_back(move);
}

void PGNBuilder::SetResult(const std::string& result)
{
	m_result = result;
}

std::string PGNBuilder::GeneratePGN() const
{
	std::string pgn;

	// Add event tag
	pgn += "[Event \"Chess Game\"]\n";

	// Add players and location tags
	pgn += "[White \"" + m_playerWhite + "\"]\n";
	pgn += "[Black \"" + m_playerBlack + "\"]\n";
	pgn += "[Site \"" + m_location + "\"]\n";

	// Add result tag
	pgn += "[Result \"" + m_result + "\"]\n\n";

	for (size_t i = 0; i < m_moves.size(); ++i)
	{
		if (i % 2 == 0)
		{
			// Add moves section
			pgn += '0' + (i/2+1);
			pgn += ". "; // Starting move number
		}
		pgn += m_moves[i];
		if (i != m_moves.size() - 1) {
			pgn += " ";
		}
	}

	return pgn;
}

void PGNBuilder::SavePGNToFile(const std::string& filePath)
{
	std::ofstream file(filePath);
	if (file.is_open()) {
		file << GeneratePGN();
		file.close();
	}
	else {
		//exception
	}
}
