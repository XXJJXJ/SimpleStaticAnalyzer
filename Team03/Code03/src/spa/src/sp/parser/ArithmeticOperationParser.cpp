#include "ArithmeticOperationParser.h"

// solution inspired from https://dev.to/j0nimost/making-a-math-interpreter-parser-52j8

shared_ptr<Expression> ArithmeticOperationParser::parse() {
    shared_ptr<Expression> leftNode = parseTerm();
    while (leftNode != nullptr && 
        !isEndOfTokens() && 
        termTokens.find(getTokenType()) != termTokens.end()) {
        string tokenValue = getTokenValue();
        getNextToken();
        shared_ptr<Expression> rightNode = parseTerm();
        PairOfArguments pairOfArguments;
        pairOfArguments.first = leftNode;
        pairOfArguments.second = rightNode;
        leftNode = make_shared<ArithmeticOperation>(tokenValue, pairOfArguments);
    }

    return leftNode;
}

shared_ptr<Expression> ArithmeticOperationParser::parseTerm() {
    shared_ptr<Expression> leftNode = parseFactor();
    while (leftNode != nullptr && 
        !isEndOfTokens() && 
        factorTokens.find(getTokenType()) != factorTokens.end()) {
        string tokenValue = getTokenValue();
        getNextToken();
        shared_ptr<Expression> rightNode = parseFactor();
        PairOfArguments pairOfArguments;
        pairOfArguments.first = leftNode;
        pairOfArguments.second = rightNode;
        leftNode = make_shared<ArithmeticOperation>(tokenValue, pairOfArguments);
    }

    return leftNode;
}

shared_ptr<Expression> ArithmeticOperationParser::parseFactor() {
    shared_ptr<Expression> leafNode = nullptr;
    if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        addParenthesis(getTokenType(), getIndex());
        getNextToken();
        leafNode = parse();
        if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
            throw SyntaxErrorException("Missing ) in Arithmetic operation");
        }
        else {
            addParenthesis(getTokenType(), getIndex());
        }
    }
    else {
        leafNode = parseLeafNode();
    }

    getNextToken();
    return leafNode;
}

shared_ptr<Expression> ArithmeticOperationParser::parseLeafNode() {
    if (getTokenType() == TokenType::INTEGER) {
        return make_shared<Constant>(getTokenValue());
    }
    else if (getTokenType() == TokenType::NAME) {
        return make_shared<Variable>(getTokenValue());
    }
    
    return nullptr;
}