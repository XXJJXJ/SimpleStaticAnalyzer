#include "PunctuationToken.h"

PunctuationToken::PunctuationToken(std::string value) : Token(getTokenTypeFromValue(value), value) {};

TokenType PunctuationToken::getTokenTypeFromValue(std::string value) {
	if (value == "(") {
		return TokenType::LEFT_PARENTHESIS;
	}
	else if (value == ")") {
		return TokenType::RIGHT_PARENTHESIS;
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
	else {
		return TokenType::DOUBLE_QUOTE;
	}
}