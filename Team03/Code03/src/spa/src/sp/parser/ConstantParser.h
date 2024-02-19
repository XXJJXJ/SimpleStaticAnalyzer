#pragma once

#include "ExpressionParser.h"
#include "common/Constant.h"

class ConstantParser : public ExpressionParser {
public:
	shared_ptr<Expression> parseEntity(Tokens& tokens) override;
};