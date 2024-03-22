#include "RelationalOperationParser.h"

shared_ptr<Expression> RelationalOperationParser::parse() {
    shared_ptr<Expression> leftRelationalFactor = parseFactor();
    updateNextToken();
    if (relationalOperators.find(getTokenType()) == relationalOperators.end()) {
        throw SyntaxErrorException("Missing Relational token");
    }
    else {
        string operation = getTokenValue();
        nextToken();
        shared_ptr<Expression> rightRelationalFactor = parseFactor();
        if (!rightRelationalFactor) {
            throw SyntaxErrorException("Missing right Relational factor");
        }

        updateNextToken();
        PairOfArguments pairOfArguments;
        pairOfArguments.first = leftRelationalFactor;
        pairOfArguments.second = rightRelationalFactor;
        return make_shared<RelationalOperation>(operation, pairOfArguments);
    }
}

shared_ptr<Expression> RelationalOperationParser::parseFactor() {
    shared_ptr<ArithmeticOperationParser> arithmeticOperationParser = make_shared<ArithmeticOperationParser>();
    arithmeticOperationParser->setArguments(getIndexPointer(), getIsSubExpression(), getIsProcessedTokenPointer());
    arithmeticOperationParser->setIsSubExpression(true);
    return arithmeticOperationParser->parseEntity(*getTokens());
}