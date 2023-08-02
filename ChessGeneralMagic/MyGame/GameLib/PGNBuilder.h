#include <iostream>
#include <string>
#include <vector>

class PGNBuilder {
public:
	PGNBuilder(const std::string& playerOne, const std::string& playerTwo, const std::string& location);

	// Getter methods
	const std::string& GetPlayerOne() const;
	const std::string& GetPlayerTwo() const;
	const std::string& GetLocation() const;
	const std::string& GetResult() const;
	const std::vector<std::string>& GetMoves() const;

	// Add a move to the moves vector
	void AddMove(const std::string& move);

	// Set the result of the game (e.g., "1-0" for white wins, "0-1" for black wins, "1/2-1/2" for draw)
	void SetResult(const std::string& result);

	// Generate the PGN file content as a string
	std::string GeneratePGN() const;

private:
	std::string m_playerOne;
	std::string m_playerTwo;
	std::string m_location;
	std::string m_result;
	std::vector<std::string> m_moves;
};
