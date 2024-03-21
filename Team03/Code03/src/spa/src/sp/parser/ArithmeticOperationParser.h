#pragma once

#include "OperationParser.h"
#include "common/ArithmeticOperation.h"
#include "common/Constant.h"
#include "common/Variable.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "../tokenizer/Token.h"
#include "unordered_set"

using namespace std;

class ArithmeticOperationParser : public OperationParser {
public:
	shared_ptr<Expression> parse() override;

private:
	unordered_set<TokenType> termTokens = { TokenType::PLUS, TokenType::MINUS };
	unordered_set<TokenType> factorTokens = { TokenType::TIMES, TokenType::DIVIDE, TokenType::MODULUS };
	shared_ptr<Expression> parseTerm();
	shared_ptr<Expression> parseFactor();
	shared_ptr<Expression> parseLeafNode();
};