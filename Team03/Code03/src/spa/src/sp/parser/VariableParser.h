#pragma once

#include "ExpressionParser.h"
#include "common/Variable.h"

class VariableParser : public ExpressionParser {
public:
	VariableParser() = default;
	shared_ptr<Expression> parseEntity(vector<shared_ptr<Token>> tokens) override;
	shared_ptr<Expression> parseEntity(shared_ptr<Token> token) override;
};