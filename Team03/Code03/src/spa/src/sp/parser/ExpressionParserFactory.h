#pragma once

#include "ExpressionParser.h"
#include "VariableParser.h"
#include "ConstantParser.h"
#include "ArithmeticOperationParser.h"
#include "ConditionalOperationParser.h"
#include "../tokenizer/Token/NameToken.h"

class ExpressionParserFactory {
    typedef Tokens Tokens;
public:
    static shared_ptr<ExpressionParser> getExpressionParser(
        Tokens &tokens,
        EntityType statementType);

private:
    static inline bool checkExpressionType(
        shared_ptr<Token> token,
        EntityType statementType);
};