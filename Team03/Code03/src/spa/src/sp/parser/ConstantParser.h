#pragma once

#include "ExpressionParser.h"
#include "common/expression/Constant.h"

class ConstantParser : public ExpressionParser {
public:
	shared_ptr<Expression> parseEntity(Tokens& tokens) override;
};