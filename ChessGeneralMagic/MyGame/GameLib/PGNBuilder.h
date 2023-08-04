#include <iostream>
#include <string>
#include <vector>

#include "EInfoPGN.h"

class PGNBuilder {
public:
	PGNBuilder();
	PGNBuilder(const std::string& playerWhite, const std::string& playerBlack, const std::string& location);

	// Getter methods
	const std::string& GetInfoPGN(EInfoPGN infoType) const;
	const std::vector<std::string> GetMoves() const;

	// Add a move to the moves vector
	void AddMove(const std::string& move);

	// Set the result of the game (e.g., "1-0" for white wins, "0-1" for black wins, "1/2-1/2" for draw)
	void SetResult(const std::string& result);

	// Generate the PGN file content as a string
	std::string GeneratePGN() const;

	void SavePGNToFile(const std::string& filePath);

private:
	std::string m_playerWhite;
	std::string m_playerBlack;
	std::string m_location;
	std::string m_result;
	std::string m_pgnStr;
	std::vector<std::string> m_moves;
};
