#include "RelationalOperationParser.h"

shared_ptr<Expression> RelationalOperationParser::parse() {
    shared_ptr<Expression> leftRelationalFactor = factor();
    updateNextToken();
    if (relationalOperators.find(getTokenType()) == relationalOperators.end()) {
        throw SyntaxErrorException("Missing Relational operator");
    }
    else {
        string operation = getTokenValue();
        getNextToken();
        shared_ptr<Expression> rightRelationalFactor = factor();
        if (!rightRelationalFactor) {
            throw SyntaxErrorException("Missing right Relational factor");
        }

        updateNextToken();
        pair<shared_ptr<Expression>, shared_ptr<Expression>> pairOfArguments;
        pairOfArguments.first = leftRelationalFactor;
        pairOfArguments.second = rightRelationalFactor;
        return make_shared<RelationalOperation>(operation, pairOfArguments);
    }
}

shared_ptr<Expression> RelationalOperationParser::factor() {
    shared_ptr<ArithmeticOperationParser> arithmeticOperationParser = make_shared<ArithmeticOperationParser>();
    arithmeticOperationParser->setArguments(getIndexPointer(), getIsSubExpression(), getIsProcessedTokenPointer());
    arithmeticOperationParser->setIsSubExpression(true);
    return arithmeticOperationParser->parseEntity(*getTokens());
}