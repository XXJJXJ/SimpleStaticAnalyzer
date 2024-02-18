#include "RelationalOperationParser.h"

shared_ptr<Expression> RelationalOperationParser::parse() {
    auto leftRelationalFactor = factor();
    updateToken();
    if (!leftRelationalFactor) {
        throw SyntaxErrorException("Missing left relational factor");
    }
    unordered_set<string> relationalOperators = {
        ">",
        ">=",
        "<",
        "<=",
        "==",
        "!=" 
    };
    if (relationalOperators.find(getTokenValue()) == relationalOperators.end()) {
        throw SyntaxErrorException("Missing relational operator");
    }

    string operation = getTokenValue();
    getNext();
    auto rightRelationalFactor = factor();
    if (!rightRelationalFactor) {
        throw SyntaxErrorException("Missing right relational factor");
    }
    updateToken();
    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
    arguments.first = leftRelationalFactor;
    arguments.second = rightRelationalFactor;
    return make_shared<RelationalOperation>(operation, arguments);
}

shared_ptr<Expression> RelationalOperationParser::factor() {
    shared_ptr<ArithmeticOperationParser> arithmeticOperationParser = make_shared<ArithmeticOperationParser>();
    arithmeticOperationParser->inheritArguments(getIndexPointer(), getIsSubExpression(), getIsProcessedTokenPointer());
    arithmeticOperationParser->setIsSubExpression(true);
    return arithmeticOperationParser->parseEntity(*getTokens());
}