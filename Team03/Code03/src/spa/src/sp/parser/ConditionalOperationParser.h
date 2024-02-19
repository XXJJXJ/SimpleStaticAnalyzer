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
};