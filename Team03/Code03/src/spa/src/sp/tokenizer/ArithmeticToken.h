#pragma once

#include "Token.h"

class ArithmeticToken : public Token {
public:
	ArithmeticToken(std::string value);
private:
	TokenType getTokenTypeFromValue(std::string value);
};