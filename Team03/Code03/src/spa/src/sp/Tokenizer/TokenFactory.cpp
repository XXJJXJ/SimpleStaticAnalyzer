#include "TokenFactory.h"

Token TokenFactory::createToken(std::string value) {
	return Token(TokenType::INVALID, value);
}