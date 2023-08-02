#pragma once

#include <string>
#include <vector>

class PGNConverter
{
public:
	PGNConverter(const std::string& pgnStr);

	std::vector<std::string> GetPGNToString(const std::string& pgnString) const;

	void SetPGNString(const std::string pgnStr);

private:
	std::string m_pgnStr;
};

