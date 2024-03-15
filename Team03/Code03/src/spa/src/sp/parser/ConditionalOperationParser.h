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
	int index;
	bool isSubExpression;
	bool isProcessedToken; 
	shared_ptr<Expression> parseRelationalOperation();
	shared_ptr<Expression> parseNotOperation();
	shared_ptr<Expression> parseAndOrOperation();
	shared_ptr<Expression> parseSubExpression();
};