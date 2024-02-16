#include "ConstantParser.h"

shared_ptr<Expression> ConstantParser::parseEntity(vector<shared_ptr<Token>> tokens) {
    return parseEntity(tokens.begin());
}

shared_ptr<Expression> ConstantParser::parseEntity(shared_ptr<Token> token) {
    if (token->getType() == TokenType::INTEGER) {
        return make_shared<Constant>(token->getValue());
    }
    
    throw SemanticErrorException("Invalid constant");
}