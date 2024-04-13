#include "ArithmeticOperationParser.h"

shared_ptr<Expression> ArithmeticOperationParser::parse() {
    return parseExpression(true);
}

bool ArithmeticOperationParser::checkTermFactorOperators(bool isTerm, TokenType tokenType) {
    return isTerm ? termOperators.find(tokenType) != termOperators.end() : factorOperators.find(tokenType)
        != factorOperators.end();
}

shared_ptr<Expression> ArithmeticOperationParser::parseTermExpression() {
    return parseExpression(false);
}

shared_ptr<Expression> ArithmeticOperationParser::parseExpression(bool isTerm) {
    shared_ptr<Expression> leftNode;
    shared_ptr<Expression> rightNode;
    leftNode = isTerm ? parseTermExpression() : parseFactorExpression();
    while (leftNode != nullptr && !isEndOfTokens() && checkTermFactorOperators(isTerm, getTokenType())) {
        string tokenValue = getTokenValue();
        nextToken();
        rightNode = isTerm ? parseTermExpression() : parseFactorExpression();
        PairOfArguments pairOfArguments{leftNode, rightNode};
        leftNode = make_shared<ArithmeticOperation>(tokenValue, pairOfArguments);
    }

    return leftNode;
}

shared_ptr<Expression> ArithmeticOperationParser::parseFactorExpression() {
    shared_ptr<Expression> leafNode = nullptr;
    TokenType tokenType = getTokenType();
    if (tokenType == TokenType::LEFT_PARANTHESIS) {
        manageParentheses(tokenType);
        nextToken();
        leafNode = parse();
        tokenType = getTokenType();
        if (tokenType == TokenType::RIGHT_PARANTHESIS) {
            manageParentheses(tokenType);
        } else {
            throw SyntaxErrorException("Missing ) token in Arithmetic operation");
        }
    } else {
        leafNode = parseLeafExpression(tokenType);
    }

    nextToken();
    return leafNode;
}

shared_ptr<Expression> ArithmeticOperationParser::parseLeafExpression(TokenType tokenType) {
    if (tokenType == TokenType::INTEGER) {
        return make_shared<Constant>(getTokenValue());
    } else if (tokenType == TokenType::NAME) {
        return make_shared<Variable>(getTokenValue());
    } else {
        return nullptr;
    }
}