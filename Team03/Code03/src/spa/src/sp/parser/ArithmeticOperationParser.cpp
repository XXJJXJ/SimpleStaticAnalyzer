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
    if (isTerm) {
        leftNode = parseTerm();
    } 
    else {
        leftNode = parseFactor();
    }
    while (checkCondition(isTerm, leftNode)) {
        tokenValue = getTokenValue();
        nextToken();
        if (isTerm) {
            rightNode = parseTerm();
        } 
        else {
            rightNode = parseFactor();
        }
        PairOfArguments pairOfArguments{leftNode, rightNode};
        leftNode = make_shared<ArithmeticOperation>(tokenValue, pairOfArguments);
    }

    return leftNode;
}

shared_ptr<Expression> ArithmeticOperationParser::parseFactor() {
    shared_ptr<Expression> leafNode = nullptr;
    if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        manageParentheses(getTokenType(), getIndex());
        nextToken();
        leafNode = parse();
        if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
            throw SyntaxErrorException("Missing ) token in Arithmetic operation");
        }
        else {
            manageParentheses(getTokenType(), getIndex());
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

bool ArithmeticOperationParser::checkCondition(bool isTerm, shared_ptr<Expression> leftNode) {
    if (isTerm) {
        return 
            leftNode != nullptr &&
            !isEndOfTokens() &&
            termTokens.find(getTokenType()) != termTokens.end();
    }
    else {
        return 
            leftNode != nullptr && 
            !isEndOfTokens() &&
            factorTokens.find(getTokenType()) != factorTokens.end();
    }
}