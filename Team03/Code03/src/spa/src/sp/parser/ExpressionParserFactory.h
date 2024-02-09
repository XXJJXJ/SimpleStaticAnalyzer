#pragma once

#include<vector>
#include "ExpressionParser.h"
#include "VariableParser.h"
#include "../Tokenizer/NameToken.h"

class ExpressionParserFactory {
    typedef vector<shared_ptr<Token>> Line;

public:
    static shared_ptr<ExpressionParser> getExpressionParser(
        vector<shared_ptr<Token>> tokens,
        string statementType);

private:
    static inline bool checkExpressionType(
        shared_ptr<Token> token,
        string_view statementType);
};