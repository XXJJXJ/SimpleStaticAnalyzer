#include "RelationalOperationParser.h"

shared_ptr<Expression> RelationalOperationParser::parse() {
    auto leftRelationalFactor = factor();
    if (!leftRelationalFactor) {
        throw SyntaxErrorException("Missing left relational factor");
    }

    unordered_set<TokenType> relationalOperators = { 
        TokenType::DOUBLE_EQUALS, 
        TokenType::GREATER_THAN, 
        TokenType::GREATER_THAN_EQUAL, 
        TokenType::LESS_THAN, 
        TokenType::LESS_THAN_EQUAL, 
        TokenType::NOT_EQUAL };
    if (relationalOperators.find(getTokenType()) == relationalOperators.end()) {
        throw SyntaxErrorException("Missing relational operator");
    }

    string operation = getTokenValue();
    getNext();
    auto rightRelationalFactor = factor();
    if (!rightRelationalFactor) {
        throw SyntaxErrorException("Missing right relational factor");
    }

    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
    arguments.first = leftRelationalFactor;
    arguments.second = rightRelationalFactor;
    return make_shared<RelationalOperation>(operation, arguments);
}

shared_ptr<Expression> RelationalOperationParser::factor() {
    shared_ptr<ArithmeticOperationParser> arithmeticOperationParser = make_shared<ArithmeticOperationParser>();
    arithmeticOperationParser->inheritArguments(getIndex(), getIsSubExpression(), getIsProcessedToken());
    arithmeticOperationParser->setIsSubExpression(true);
    return arithmeticOperationParser->parseEntity(*getTokens());
}