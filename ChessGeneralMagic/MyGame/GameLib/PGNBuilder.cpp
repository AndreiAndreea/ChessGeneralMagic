#include "PGNBuilder.h"

PGNBuilder::PGNBuilder(const std::string& playerOne, const std::string& playerTwo, const std::string& location) 
	: m_playerOne(playerOne)
	, m_playerTwo(playerTwo)
	, m_location(location)
{
	m_result = "*"; // Default result as "*" (unfinished game)
}

const std::string& PGNBuilder::GetPlayerOne() const
{
	return m_playerOne;
}

const std::string& PGNBuilder::GetPlayerTwo() const
{
	return m_playerTwo;
}

const std::string& PGNBuilder::GetLocation() const
{
	return m_location;
}

const std::string& PGNBuilder::GetResult() const
{
	return m_result;
}

const std::vector<std::string>& PGNBuilder::GetMoves() const
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
	pgn += "[White \"" + m_playerOne + "\"]\n";
	pgn += "[Black \"" + m_playerTwo + "\"]\n";
	pgn += "[Site \"" + m_location + "\"]\n";

	// Add result tag
	pgn += "[Result \"" + m_result + "\"]\n\n";

	// Add moves section
	pgn += "1. "; // Starting move number
	for (size_t i = 0; i < m_moves.size(); ++i)
	{
		pgn += m_moves[i];
		if (i != m_moves.size() - 1) {
			pgn += " ";
		}
	}

	return pgn;
}
