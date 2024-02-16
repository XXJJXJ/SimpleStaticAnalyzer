#pragma once

#include "OperationParser.h"
#include "common/ArithmeticOperation.h"
#include "common/Constant.h"
#include "common/Variable.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "../tokenizer/Token.h"

using namespace std;

class ArithmeticOperationParser : public OperationParser {
public:
	ArithmeticOperationParser() = default;
	shared_ptr<Expression> parse() override;

private:
	vector<TokenType> termTokens = { TokenType::PLUS, TokenType::MINUS };
	vector<TokenType> factorTokens = { TokenType::TIMES, TokenType::DIVIDE, TokenType::MODULUS };
	shared_ptr<Expression> term();
	shared_ptr<Expression> factor();
};