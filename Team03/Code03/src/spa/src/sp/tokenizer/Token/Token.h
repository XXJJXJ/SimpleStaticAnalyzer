#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

enum class TokenType {
	LEFT_PARANTHESIS,
	RIGHT_PARANTHESIS,
	LEFT_BRACE,
	RIGHT_BRACE,
	SEMICOLON,
	DOUBLE_QUOTE,
	SINGLE_EQUAL,
	PLUS,
	MINUS,
	TIMES,
	DIVIDE,
	MODULUS,
	LESS_THAN,
	LESS_THAN_EQUAL,
	GREATER_THAN,
	GREATER_THAN_EQUAL,
	DOUBLE_EQUALS,
	NOT_EQUAL,
	AND,
	OR,
	NOT,
	NAME,
	INTEGER,
	INVALID
};

class Token {
private:
	const TokenType type;
	const string value;
public:
	Token(TokenType type, std::string value);
	std::string getValue();
	TokenType getType();
};