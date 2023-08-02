#include "PGNConverter.h"

PGNConverter::PGNConverter(const std::string& pgnStr) : m_pgnStr(pgnStr)
{}

std::vector<std::string> PGNConverter::GetPGNToString(const std::string& pgnString) const
{
	// Vector to store individual moves
	std::vector<std::string> moves;

	// Temporary string to hold a move while processing
	std::string currentMove;

	// Iterate through each character in the PGN string
	for (char c : pgnString) {
		if (c == '+' || c == '#') {
			// Skip the '+' sign for check and '#' sign for mate
			continue;
		}
		else if (c == ' ' || c == '\n') {
			// If space or newline is encountered, the move is complete
			if (!currentMove.empty()) {
				// Remove the move number prefix (e.g., "1. ", "2. ", etc.)
				size_t prefixPos = currentMove.find('.');
				if (prefixPos != std::string::npos) {
					currentMove.erase(0, prefixPos + 1);
				}

				moves.push_back(currentMove);
				currentMove.clear();
			}
		}
		else {
			// Add the character to the current move
			currentMove += c;
		}
	}

	// Add the last move if it exists
	if (!currentMove.empty()) {
		// Remove the move number prefix from the last move
		size_t prefixPos = currentMove.find('.');
		if (prefixPos != std::string::npos) {
			currentMove.erase(0, prefixPos + 1);
		}

		moves.push_back(currentMove);
	}

	return moves;
}

void PGNConverter::SetPGNString(const std::string pgnStr)
{
	m_pgnStr = pgnStr;
}
