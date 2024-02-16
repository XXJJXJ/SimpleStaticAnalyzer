#include "VariableParser.h"

shared_ptr<Expression> VariableParser::parseEntity(vector<shared_ptr<Token>>& tokens) {
    shared_ptr<Token> token = tokens.front(); 
    if (token->getType() == TokenType::NAME) {
        return make_shared<Variable>(token->getValue());
    }

    throw SemanticErrorException("Invalid constant");
}