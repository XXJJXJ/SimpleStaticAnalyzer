#pragma once

#include <unordered_set>
#include "OperationParser.h"
#include "ArithmeticOperationParser.h"
#include "common/RelationalOperation.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "../tokenizer/Token.h"
#include "unordered_set"

using namespace std;

class RelationalOperationParser : public OperationParser {
public:
	shared_ptr<Expression> parse() override;

private:
	shared_ptr<Expression> parseFactor();
	unordered_set<TokenType> relationalOperators = {
        TokenType::GREATER_THAN,
        TokenType::GREATER_THAN_EQUAL,
        TokenType::LESS_THAN,
        TokenType::LESS_THAN_EQUAL,
        TokenType::DOUBLE_EQUALS,
        TokenType::NOT_EQUAL
    };
};