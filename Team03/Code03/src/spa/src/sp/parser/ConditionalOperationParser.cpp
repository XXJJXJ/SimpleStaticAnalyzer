#include "ConditionalOperationParser.h"

shared_ptr<Expression> ConditionalOperationParser::parse() {
    int index = *getIndexPointer();
    try {
        shared_ptr<Expression> relationalExpression = parseRelationalExpression();
        if (relationalExpression) {
            setNextToken();
            return relationalExpression;
        }
    }
    catch (SpaException& e) {
        string check = "Initial parsing of Relational expression failed. Presence of sub expressions.";
    }

    return parseSubExpression(index, getTokenType());
}

shared_ptr<Expression> ConditionalOperationParser::parseRelationalExpression() {
    shared_ptr<RelationalOperationParser> relationalOperationParser = make_shared<RelationalOperationParser>();
    relationalOperationParser->setPairOfArguments(
        getIsSubExpressionPointer(),
        getIndexPointer(),  
        getIsProcessedTokenPointer());
    setIsSubExpression(false);
    shared_ptr<Expression> relationalExpression = relationalOperationParser->parseEntity(*getTokens());
    if (relationalExpression) {
        PairOfArguments pairOfArguments{relationalExpression, nullptr}; 
        return make_shared<ConditionalOperation>("relationalExpression", pairOfArguments);
    }
    else {
        return nullptr;
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseNotOperation() {
    if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        setIsSubExpression(true);
        nextToken();
        shared_ptr<Expression> subExpression = parse();
        if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
            throw SyntaxErrorException("Missing ) token in Conditional expression");
        }
        else {
            nextToken();
            PairOfArguments pairOfArguments{subExpression, nullptr};
            return make_shared<ConditionalOperation>("!", pairOfArguments);
        }
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseAndOrOperation() {
    shared_ptr<Expression> leftSubExpression = parse();
    if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
        throw SyntaxErrorException("Missing ) token in Conditional expression");
    }
    else {
        nextToken();
        string operation = getTokenValue();
        if (!(getTokenType() == TokenType::OR || getTokenType() == TokenType::AND)) {
            throw SyntaxErrorException("Missing || or && token in Conditional expression");
        }
        else {
            nextToken();
            if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
                setIsSubExpression(true);
                nextToken();
                shared_ptr<Expression> rightSubExpression = parse();
                nextToken();
                if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
                    throw SyntaxErrorException("Missing ) token in Conditional expression");
                }
                else {
                    PairOfArguments pairOfArguments{leftSubExpression, rightSubExpression};
                    return make_shared<ConditionalOperation>(operation, pairOfArguments);
                }
            }
            else {
                throw SyntaxErrorException("Missing ( token in Conditional expression");
            }
        }
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseSubExpression(int index, TokenType tokenType) {
    setPairOfArguments(
        getIsSubExpressionPointer(),
        make_shared<int>(index),
        getIsProcessedTokenPointer());
    if (tokenType == TokenType::NOT) {
        nextToken();
        return parseNotOperation();
    }
    else if (tokenType == TokenType::LEFT_PARANTHESIS) {
        nextToken();
        setIsSubExpression(true);
        return parseAndOrOperation();
    }
    else {
        throw SyntaxErrorException("Invalid Conditional expression");
    }
}