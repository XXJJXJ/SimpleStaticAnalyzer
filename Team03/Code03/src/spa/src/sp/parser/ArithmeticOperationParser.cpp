#include "ArithmeticOperationParser.h"

// solution inspired from https://dev.to/j0nimost/making-a-math-interpreter-parser-52j8

shared_ptr<Expression> ArithmeticOperationParser::parse() {
    shared_ptr<Expression> leftNode = term();
    while (!isEndOfStatement() && 
        leftNode != nullptr && 
        count(termTokens.begin(), termTokens.end(), getTokenType())) {
        string tokenValue = getTokenValue();
        getNextToken();
        shared_ptr<Expression> rightNode = term();
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
        arguments.first = leftNode;
        arguments.second = rightNode;
        leftNode = make_shared<ArithmeticOperation>(tokenValue, arguments);
    }

    return leftNode;
}

shared_ptr<Expression> ArithmeticOperationParser::term() {
    shared_ptr<Expression> leftNode = factor();
    while (!isEndOfStatement() && 
        leftNode != nullptr && 
        count(factorTokens.begin(), factorTokens.end(), getTokenType())) {
        string tokenValue = getTokenValue();
        getNextToken();
        shared_ptr<Expression> rightNode = factor();
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
        arguments.first = leftNode;
        arguments.second = rightNode;
        leftNode = make_shared<ArithmeticOperation>(tokenValue, arguments);
    }

    return leftNode;
}

shared_ptr<Expression> ArithmeticOperationParser::factor() {
    shared_ptr<Expression> leafNode = nullptr;
    if (getTokenValue() == "(") {
        addParenthesis(getTokenValue(), getIndex());
        getNextToken();
        leafNode = parse();
        if (getTokenValue() != ")") {
            throw SyntaxErrorException("Missing ) in arithmetic operation");
        }
        addParenthesis(getTokenValue(), getIndex());
    }
    else if (getTokenType() == TokenType::INTEGER) {
        leafNode = make_shared<Constant>(getTokenValue());
    }
    else if (getTokenType() == TokenType::NAME) {
        leafNode = make_shared<Variable>(getTokenValue());
    }

    getNextToken();
    return leafNode;
}