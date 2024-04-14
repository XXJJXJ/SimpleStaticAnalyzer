#pragma once

#include "Token.h"

class PunctuationToken : public Token {
public:
    PunctuationToken(std::string value);
private:
    TokenType getTokenTypeFromValue(std::string value);
};