#pragma once

#include <string>
#include <vector>

class PGNConverter
{
public:
	PGNConverter();
	PGNConverter(const std::string& pgnStr);

	std::vector<std::string> ConvertToPGNStringMoves() const;

	void SetPGNString(const std::string pgnStr);

	void LoadPGNFromFile(const std::string& filePath);

private:
	std::string m_pgnStr;
};

