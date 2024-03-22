#include "ConditionalOperationParser.h"

shared_ptr<Expression> ConditionalOperationParser::parse() {
    try {
        index = *getIndexPointer();
        isSubExpression = getIsSubExpression();
        isProcessedToken = *getIsProcessedTokenPointer();
        shared_ptr<Expression> relationalExpression = parseRelationalOperation();
        if (relationalExpression) {
            return relationalExpression;
        }
    }
    catch (SpaException& e) {
        string check = "Initial parsing of Relational operation failed";
    }

    setArguments(
        make_shared<int>(index),
        isSubExpression,
        make_shared<bool>(isProcessedToken));

    return parseSubExpression();
}

shared_ptr<Expression> ConditionalOperationParser::parseRelationalOperation() {
    shared_ptr<RelationalOperationParser> relationalOperationParser = make_shared<RelationalOperationParser>();
    relationalOperationParser->setArguments(getIndexPointer(), getIsSubExpression(), getIsProcessedTokenPointer());
    shared_ptr<Expression> relationalExpression = relationalOperationParser->parseEntity(*getTokens());
    setIsSubExpression(false);

    if (relationalExpression) {
        PairOfArguments arguments;
        arguments.first = relationalExpression; 
        updateNextToken();
        return make_shared<ConditionalOperation>("relationalExpression", arguments);
    }
    else {
        return nullptr;
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseNotOperation() {
    nextToken();
    if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        nextToken();
        setIsSubExpression(true);
        shared_ptr<Expression> conditionalExpression = parse();
        if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
            throw SyntaxErrorException("Missing ) in Conditional operation");
        }
        else {
            nextToken();
            PairOfArguments arguments;
            arguments.first = conditionalExpression;
            return make_shared<ConditionalOperation>("!", arguments);
        }
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseAndOrOperation() {
    nextToken();
    checkTokens();
    setIsSubExpression(true);
    shared_ptr<Expression> leftConditionalExpression = parse();
    if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
        throw SyntaxErrorException("Missing ) in Conditional operation");
    }

    nextToken();
    string operation = getTokenValue();
    if (!(getTokenType() == TokenType::OR || getTokenType() == TokenType::AND)) {
        throw SyntaxErrorException("Missing || or && in Conditional operation");
    }
    else {
        nextToken();

        if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
            nextToken();
            setIsSubExpression(true);
            shared_ptr<Expression> rightConditionalExpression = parse();
            if (*(getIndexPointer().get()) < getTokens()->size()) {
                nextToken();
            }
            if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
                throw SyntaxErrorException("Missing ) in Conditional operation");
            } else {
                PairOfArguments pairOfArguments;
                pairOfArguments.first = leftConditionalExpression;
                pairOfArguments.second = rightConditionalExpression;
                return make_shared<ConditionalOperation>(operation, pairOfArguments);
            }
        }
        else {
            throw SyntaxErrorException("Missing ( in Conditional operation");
        }
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseSubExpression() {
    if (getTokenType() == TokenType::NOT) {
        return parseNotOperation();
    }
    else if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        return parseAndOrOperation();
    }

    throw SyntaxErrorException("Invalid Conditional operation");
}