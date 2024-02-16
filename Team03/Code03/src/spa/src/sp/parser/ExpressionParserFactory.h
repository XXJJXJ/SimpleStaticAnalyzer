#pragma once

#include "ExpressionParser.h"
#include "VariableParser.h"
#include "ConstantParser.h"
#include "ArithmeticOperationParser.h"
#include "ConditionalOperationParser.h"
#include "../tokenizer/NameToken.h"

class ExpressionParserFactory {
    typedef vector<shared_ptr<Token>> Tokens;

public:
    static shared_ptr<ExpressionParser> getExpressionParser(
        vector<shared_ptr<Token>>& tokens,
        string statementType);

private:
    static inline bool checkExpressionType(
        shared_ptr<Token> token,
        string_view statementType);
};