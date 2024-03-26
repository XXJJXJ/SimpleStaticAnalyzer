#pragma once

#include "OperationParser.h"
#include "RelationalOperationParser.h"
#include "common/ConditionalOperation.h"
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
	shared_ptr<Expression> parseSubExpression(int index, TokenType tokenType);
	shared_ptr<Expression> parseNotSubExpression();
	shared_ptr<Expression> parseAndOrSubExpression();
};