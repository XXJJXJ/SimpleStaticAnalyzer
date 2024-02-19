#include "ConstantParser.h"

shared_ptr<Expression> ConstantParser::parseEntity(Tokens& tokens) {
    shared_ptr<Token> token = tokens.front();
    if (token->getType() == TokenType::INTEGER) {
        return make_shared<Constant>(token->getValue());
    }

    throw SemanticErrorException("Invalid constant");
}