#pragma once

#include "OperationParser.h"
#include "RelationalOperationParser.h"
#include "common/expression/ConditionalOperation.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "../tokenizer/Token.h"

using namespace std;

class ConditionalOperationParser : public OperationParser {
public:
	shared_ptr<Expression> parse() override;

private:
	bool isSubExpression;
	bool isProcessedToken; 
	shared_ptr<Expression> parseRelationalExpression();
	shared_ptr<Expression> parseExpression(int index, TokenType tokenType);
	shared_ptr<Expression> parseSubExpression(string operation, shared_ptr<Expression> subExpression);
	shared_ptr<Expression> parseAndOrSubExpression();
};