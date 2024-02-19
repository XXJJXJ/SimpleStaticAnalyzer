#include "RelationalToken.h"

RelationalToken::RelationalToken(std::string value) : Token(getTokenTypeFromValue(value), value) {};

TokenType RelationalToken::getTokenTypeFromValue(std::string value) {
	if (value == "&&") {
		return TokenType::AND;
	}
	else if (value == "||") {
		return TokenType::OR;
	}
	else if (value == "!") {
		return TokenType::NOT;
	}
	else {
		return TokenType::INVALID;
	}
}