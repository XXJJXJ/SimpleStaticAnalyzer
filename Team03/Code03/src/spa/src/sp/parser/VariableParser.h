#pragma once

#include "ExpressionParser.h"
#include "common/Variable.h"

class VariableParser : public ExpressionParser {
public:
	shared_ptr<Expression> parseEntity(Tokens& tokens) override;
};