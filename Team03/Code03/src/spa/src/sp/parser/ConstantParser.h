#pragma once

#include "ExpressionParser.h"
#include "common/Constant.h"

class ConstantParser : public ExpressionParser {
public:
	shared_ptr<Expression> parseEntity(vector<shared_ptr<Token>>& tokens) override;
	shared_ptr<Expression> parseEntity(shared_ptr<Token>& token) override;
};