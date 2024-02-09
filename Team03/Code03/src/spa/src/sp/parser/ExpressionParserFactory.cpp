#include "ExpressionParserFactory.h"

shared_ptr<ExpressionParser> ExpressionParserFactory::getExpressionParser(
    vector<shared_ptr<Token>> tokens, 
    string statementType) {
    if (checkExpressionType(tokens.front(), "variable")) {
        return make_shared<VariableParser>();
    }

    return nullptr;
}

bool ExpressionParserFactory::checkExpressionType(
    shared_ptr<Token> token,
    string_view statementType) {
    if (token->getType() == TokenType::NAME) {
        return statementType == "variable";
    }

    return statementType == "operation";
}