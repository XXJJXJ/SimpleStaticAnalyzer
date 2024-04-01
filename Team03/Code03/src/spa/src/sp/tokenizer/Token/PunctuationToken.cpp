#include "PunctuationToken.h"

PunctuationToken::PunctuationToken(std::string value) : Token(getTokenTypeFromValue(value), value) {};

TokenType PunctuationToken::getTokenTypeFromValue(std::string value) {
	if (value == "(") {
		return TokenType::LEFT_PARANTHESIS;
	}
	else if (value == ")") {
		return TokenType::RIGHT_PARANTHESIS;
	}
	else if (value == "{") {
		return TokenType::LEFT_BRACE;
	}
	else if (value == "}") {
		return TokenType::RIGHT_BRACE;
	}
	else if (value == ";") {
		return TokenType::SEMICOLON;
	}
	else if (value == "\"") {
		return TokenType::DOUBLE_QUOTE;
	}
	else {
		return TokenType::INVALID;
	}
}