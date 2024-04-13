#include "RelationalOperationParser.h"

shared_ptr<Expression> RelationalOperationParser::parse() {
    shared_ptr<Expression> leftRelationalFactor = parseRelationalFactor();
    setNextToken();
    if (relationalOperators.find(getTokenType()) != relationalOperators.end()) {
        string operation = getTokenValue();
        nextToken();
        shared_ptr<Expression> rightRelationalFactor = parseRelationalFactor();
        if (rightRelationalFactor) {
            PairOfArguments pairOfArguments{leftRelationalFactor, rightRelationalFactor};
            return make_shared<RelationalOperation>(operation, pairOfArguments);
        }

        throw SyntaxErrorException("Missing relational factor in Arithmetic expression");
    }

    throw SyntaxErrorException("Missing > or >= or < or <= or == or != token");
}

shared_ptr<Expression> RelationalOperationParser::parseRelationalFactor() {
    shared_ptr<ArithmeticOperationParser> arithmeticOperationParser = make_shared<ArithmeticOperationParser>();
    arithmeticOperationParser->setPairOfArguments(getIsSubExpressionPointer(),
                                                  getIndexPointer(),
                                                  getIsProcessedTokenPointer());
    arithmeticOperationParser->setIsSubExpression(true);
    return arithmeticOperationParser->parseEntity(*getTokens());
}