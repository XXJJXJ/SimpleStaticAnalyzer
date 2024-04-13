#pragma once

#include "Token.h"

class ConditionalToken : public Token {
public:
    ConditionalToken(std::string value);
private:
    TokenType getTokenTypeFromValue(std::string value);
};