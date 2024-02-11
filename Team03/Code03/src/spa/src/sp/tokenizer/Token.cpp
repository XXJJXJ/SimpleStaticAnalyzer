#include "Token.h"

Token::Token(TokenType type, std::string value) : type(type), value(value) {};

std::string Token::getValue() { return value; }

TokenType Token::getType() { return type; }