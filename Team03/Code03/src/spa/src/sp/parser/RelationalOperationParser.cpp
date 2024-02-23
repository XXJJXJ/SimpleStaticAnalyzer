#include "RelationalOperationParser.h"

shared_ptr<Expression> RelationalOperationParser::parse() {
    auto leftRelationalFactor = factor();

    updateNextToken();
    unordered_set<TokenType> relationalOperators = {
        TokenType::GREATER_THAN,
        TokenType::GREATER_THAN_EQUAL,
        TokenType::LESS_THAN,
        TokenType::LESS_THAN_EQUAL,
        TokenType::DOUBLE_EQUALS,
        TokenType::NOT_EQUAL
    };

    if (relationalOperators.find(getTokenType()) == relationalOperators.end()) {
        throw SyntaxErrorException("Missing Relational operator");
    }

    string operation = getTokenValue();
    getNextToken();
    auto rightRelationalFactor = factor();
    if (!rightRelationalFactor) {
        throw SyntaxErrorException("Missing right Relational factor");
    }

    updateNextToken();
    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
    arguments.first = leftRelationalFactor;
    arguments.second = rightRelationalFactor;
    return make_shared<RelationalOperation>(operation, arguments);
}

shared_ptr<Expression> RelationalOperationParser::factor() {
    shared_ptr<ArithmeticOperationParser> arithmeticOperationParser = make_shared<ArithmeticOperationParser>();
    arithmeticOperationParser->setArguments(getIndexPointer(), getIsSubExpression(), getIsProcessedTokenPointer());
    arithmeticOperationParser->setIsSubExpression(true);
    return arithmeticOperationParser->parseEntity(*getTokens());
}