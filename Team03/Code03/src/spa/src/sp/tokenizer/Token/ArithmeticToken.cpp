#include "ArithmeticToken.h"

ArithmeticToken::ArithmeticToken(std::string value) : Token(getTokenTypeFromValue(value), value) {};

TokenType ArithmeticToken::getTokenTypeFromValue(std::string value) {
	if (value == "=") {
		return TokenType::SINGLE_EQUAL;
	}
	else if (value == "+") {
		return TokenType::PLUS;
	}
	else if (value == "-") {
		return TokenType::MINUS;
	}
	else if (value == "*") {
		return TokenType::TIMES;
	}
	else if (value == "/") {
		return TokenType::DIVIDE;
	}
	else if (value == "%") {
		return TokenType::MODULUS;
	}
	else {
		return TokenType::INVALID;
	}
}