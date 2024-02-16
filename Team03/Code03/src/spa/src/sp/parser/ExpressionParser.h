#pragma once

#include "common/Expression.h"
#include "common/Statement.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "EntityParser.h"

class ExpressionParser : public EntityParser<Expression> {
public:
	virtual shared_ptr<Expression> parseEntity(vector<shared_ptr<Token>>& tokens) = 0;
	virtual shared_ptr<Expression> parseEntity(shared_ptr<Token>& token) = 0;
};