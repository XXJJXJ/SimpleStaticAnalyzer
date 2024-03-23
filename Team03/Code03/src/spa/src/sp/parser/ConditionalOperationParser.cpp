#include "ConditionalOperationParser.h"

shared_ptr<Expression> ConditionalOperationParser::parse() {
    try {
        index = *getIndexPointer();
        shared_ptr<Expression> relationalExpression = parseRelationalOperation();
        if (relationalExpression) {
            return relationalExpression;
        }
    }
    catch (SpaException& e) {
        string check = "Initial parsing of Relational operation failed. Presence of subexpressions.";
    }

    setPairOfArguments(
        getIsSubExpression(),
        make_shared<int>(index),
        getIsProcessedTokenPointer());

    return parseSubExpression();
}

shared_ptr<Expression> ConditionalOperationParser::parseRelationalOperation() {
    shared_ptr<RelationalOperationParser> relationalOperationParser = make_shared<RelationalOperationParser>();
    relationalOperationParser->setPairOfArguments(
        getIsSubExpression(),
        getIndexPointer(),  
        getIsProcessedTokenPointer());
    setIsSubExpression(false);
    shared_ptr<Expression> relationalExpression = relationalOperationParser->parseEntity(*getTokens());
    if (relationalExpression) {
        setNextToken();
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
    setIsSubExpression(true);
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
                if (*getIndexPointer() < getTokens()->size()) {
                    nextToken();
                }
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

shared_ptr<Expression> ConditionalOperationParser::parseSubExpression() {
    if (getTokenType() == TokenType::NOT) {
        nextToken();
        return parseNotOperation();
    }
    else if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        nextToken();
        return parseAndOrOperation();
    }

    throw SyntaxErrorException("Invalid Conditional expression");
}