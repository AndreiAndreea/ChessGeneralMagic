#include "PGNConverter.h"
#include <fstream>

PGNConverter::PGNConverter()
{}

PGNConverter::PGNConverter(const std::string& pgnStr)
	: m_pgnStr(pgnStr)
{}

std::vector<std::string> PGNConverter::ConvertToPGNStringMoves() const
{
	// Vector to store individual moves
	std::vector<std::string> moves;

	// Temporary string to hold a move while processing
	std::string currentMove;

	// Iterate through each character in the PGN string
	for (char c : m_pgnStr) {
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

				if(currentMove.size())
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

void PGNConverter::LoadPGNFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (file.is_open()) {
		std::string pgnString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();
		//std::cout << "PGN loaded from: " << filePath << std::endl;
		for (int i = 0; i < pgnString.size() ; i++)
		{
			if (pgnString[i] == '\n' && pgnString[i + 1] == '\n')
			{
				m_pgnStr = pgnString.substr(i+2, pgnString.size() - i+2);
				i = pgnString.size();
			}
		}
	}
	else {
		//exception
		
		//std::cerr << "Error: Unable to open file for reading: " << filePath << std::endl;
		m_pgnStr = "";
	}
}
