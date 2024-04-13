#include "ExpressionParserFactory.h"

shared_ptr<ExpressionParser> ExpressionParserFactory::getExpressionParser(Tokens &tokens, EntityType statementType) {
    if (tokens.size() == 1) {
        if (checkExpressionType(tokens.front(), EntityType::Variable)) {
            return make_shared<VariableParser>();
        } else if (checkExpressionType(tokens.front(), EntityType::Constant)) {
            return make_shared<ConstantParser>();
        } else if (!checkExpressionType(tokens.front(), EntityType::Operation)) {
            return nullptr;
        }
    } else if (statementType == EntityType::Assign) {
        return make_shared<ArithmeticOperationParser>();
    } else if (statementType == EntityType::If || statementType == EntityType::While) {
        return make_shared<ConditionalOperationParser>();
    } else {
        return nullptr;
    }
}

bool ExpressionParserFactory::checkExpressionType(shared_ptr<Token> token, EntityType statementType) {
    if (token->getType() == TokenType::NAME) {
        return statementType == EntityType::Variable;
    } else {
        if (token->getType() == TokenType::INTEGER) {
            return statementType == EntityType::Constant;
        } else {
            return statementType == EntityType::Operation;
        }
    }
}