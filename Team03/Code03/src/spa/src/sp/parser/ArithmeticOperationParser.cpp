#include "ArithmeticOperationParser.h"

shared_ptr<Expression> ArithmeticOperationParser::parse() {
    return parseExpression(true);
}

shared_ptr<Expression> ArithmeticOperationParser::parseTerm() {
    return parseExpression(false);
}

shared_ptr<Expression> ArithmeticOperationParser::parseExpression(bool isTerm) {
    string tokenValue;
    shared_ptr<Expression> leftNode;
    shared_ptr<Expression> rightNode;
    leftNode = isTerm ? parseTerm() : parseFactor();
    while (leftNode != nullptr && !isEndOfTokens() && checkTermFactor(isTerm)) {
        tokenValue = getTokenValue();
        nextToken();
        rightNode = isTerm ? parseTerm() : parseFactor();
        PairOfArguments pairOfArguments{leftNode, rightNode};
        leftNode = make_shared<ArithmeticOperation>(tokenValue, pairOfArguments);
    }

    return leftNode;
}

shared_ptr<Expression> ArithmeticOperationParser::parseFactor() {
    shared_ptr<Expression> leafNode = nullptr;
    TokenType tokenType = getTokenType();
    if (tokenType == TokenType::LEFT_PARANTHESIS) {
        manageParentheses(tokenType);
        nextToken();
        leafNode = parse();
        tokenType = getTokenType();
        if (tokenType != TokenType::RIGHT_PARANTHESIS) {
            throw SyntaxErrorException("Missing ) token in Arithmetic operation");
        }
        else {
            manageParentheses(tokenType);
        }
    }
    else {
        leafNode = parseLeafNode();
    }

    nextToken();
    return leafNode;
}

shared_ptr<Expression> ArithmeticOperationParser::parseLeafNode() {
    if (getTokenType() == TokenType::INTEGER) {
        return make_shared<Constant>(getTokenValue());
    }
    else if (getTokenType() == TokenType::NAME) {
        return make_shared<Variable>(getTokenValue());
    }
    else {
        return nullptr;
    }
}

bool ArithmeticOperationParser::checkTermFactor(bool isTerm) {
    return isTerm ?
            termTokens.find(getTokenType()) != termTokens.end() :
            factorTokens.find(getTokenType()) != factorTokens.end();
}