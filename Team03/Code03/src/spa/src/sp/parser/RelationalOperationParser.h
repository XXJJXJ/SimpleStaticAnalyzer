#pragma once

#include <unordered_set>
#include "OperationParser.h"
#include "ArithmeticOperationParser.h"
#include "common/RelationalOperation.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "../tokenizer/Token.h"

using namespace std;

class RelationalOperationParser : public OperationParser {
public:
	shared_ptr<Expression> parse() override;

private:
	shared_ptr<Expression> factor();
};