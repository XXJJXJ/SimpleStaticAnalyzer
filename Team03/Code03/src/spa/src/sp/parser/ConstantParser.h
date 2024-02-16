#pragma once

#include "ExpressionParser.h"
#include "common/Constant.h"

class ConstantParser : public ExpressionParser {
public:
	ConstantParser() = default;
	shared_ptr<Expression> parseEntity(vector<shared_ptr<Token>>& tokens) override;
};