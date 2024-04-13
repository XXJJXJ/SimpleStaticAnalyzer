#include "TokenFactory.h"

shared_ptr<Token> TokenFactory::createToken(std::string value) {
	return make_shared<Token>(TokenType::INVALID, value);
}