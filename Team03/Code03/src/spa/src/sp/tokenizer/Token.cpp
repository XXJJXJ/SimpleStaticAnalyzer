#include "Token.h"

Token::Token(TokenType type, std::string value) : type(type), value(value) {};

std::string Token::getValue() { return value; }

TokenType Token::getType() { return type; }

std::string Token::getTypeAsString() {
	if (type == TokenType::LEFT_PARANTHESIS || type == TokenType::RIGHT_PARANTHESIS || type == TokenType::LEFT_BRACE || type == TokenType::RIGHT_BRACE || type == TokenType::SEMICOLON || type == TokenType::DOUBLE_QUOTE) {
		return "Punctuation Token";
	}
	else if (type == TokenType::PLUS || type == TokenType::MINUS || type == TokenType::TIMES || type == TokenType::DIVIDE || type == TokenType::MODULUS || type == TokenType::SINGLE_EQUAL) {
		return "Arithmetic Token";
	}
	else if (type == TokenType::LESS_THAN || type == TokenType::LESS_THAN_EQUAL || type == TokenType::GREATER_THAN || type == TokenType::GREATER_THAN_EQUAL || type == TokenType::DOUBLE_EQUALS || type == TokenType::NOT_EQUAL) {
		return "Conditional Token";
	}
	else if (type == TokenType::AND || type == TokenType::OR || type == TokenType::NOT) {
		return "Relational Token";
	}
	else if (type == TokenType::NAME) {
		return "Name Token";
	}
	else if (type == TokenType::INTEGER) {
		return "Integer Token";
	}
	else {
		return "Invalid Token";
	}
}