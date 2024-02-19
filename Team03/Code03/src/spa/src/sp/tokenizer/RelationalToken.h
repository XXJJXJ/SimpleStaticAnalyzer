#pragma once

#include "Token.h"

class RelationalToken : public Token {
public:
	RelationalToken(std::string value);
private:
	TokenType getTokenTypeFromValue(std::string value);
};