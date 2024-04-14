#pragma once

#include "common/expression/Expression.h"
#include "common/statement/Statement.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "EntityParser.h"

class ExpressionParser : public EntityParser<Expression> {
public:
    typedef Tokens Tokens;
    virtual shared_ptr<Expression> parseEntity(Tokens &tokens) = 0;
};