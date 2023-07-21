#pragma once

#include <stdexcept>

class ChessExceptions : std::runtime_error
{
public:
	ChessExceptions(const std::string& errorMessage);
};

