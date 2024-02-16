#include "ExpressionParserFactory.h"

shared_ptr<ExpressionParser> ExpressionParserFactory::getExpressionParser(
    vector<shared_ptr<Token>>& tokens, 
    string statementType) {

    if (checkExpressionType(tokens.front(), "variable")) {
        return make_shared<VariableParser>();
    }

    if (checkExpressionType(tokens.front(), "constant")) {
        return make_shared<ConstantParser>();
    }

    if (!checkExpressionType(tokens.front(), "operation")) {
        return nullptr;
    }

    if (checkExpressionType(tokens.front(), "assign")) {
        return make_shared<ArithmeticOperationParser>();
    }

    if (checkExpressionType(tokens.front(), "if") || checkExpressionType(tokens.front(), "while")) {
        return make_shared<ConditionalOperationParser>();
    }

    return nullptr;
}

bool ExpressionParserFactory::checkExpressionType(
    shared_ptr<Token> token,
    string_view statementType) {
    if (token->getType() == TokenType::NAME) {
        return statementType == "variable";
    }

    if (token->getType() == TokenType::INTEGER) {
        return statementType == "constant";
    }

    return statementType == "operation";
}