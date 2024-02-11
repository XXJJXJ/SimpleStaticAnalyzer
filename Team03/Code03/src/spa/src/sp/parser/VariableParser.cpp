#include "VariableParser.h"

shared_ptr<Expression> VariableParser::parseEntity(vector<shared_ptr<Token>> tokens) {
    return parseEntity(tokens.front());
}

shared_ptr<Expression> VariableParser::parseEntity(shared_ptr<Token> token) {
    return make_shared<Variable>(token->getValue());
}
