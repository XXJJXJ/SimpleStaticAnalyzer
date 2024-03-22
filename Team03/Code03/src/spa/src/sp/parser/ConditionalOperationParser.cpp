#include "ConditionalOperationParser.h"

shared_ptr<Expression> ConditionalOperationParser::parse() {
    try {
        index = *getIndexPointer();
        isSubExpression = getIsSubExpression();
        shared_ptr<Expression> relationalExpression = parseRelationalOperation();
        if (relationalExpression) {
            return relationalExpression;
        }
    }
    catch (SpaException& e) {
        string check = "Initial parsing of Relational operation failed";
    }

    setArguments(
        isSubExpression,
        make_shared<int>(index),
        make_shared<bool>(*getIsProcessedTokenPointer()));

    return parseSubExpression();
}

shared_ptr<Expression> ConditionalOperationParser::parseRelationalOperation() {
    shared_ptr<RelationalOperationParser> relationalOperationParser = make_shared<RelationalOperationParser>();
    relationalOperationParser->setArguments(
        getIsSubExpression(),
        getIndexPointer(),  
        getIsProcessedTokenPointer());
    shared_ptr<Expression> relationalExpression = relationalOperationParser->parseEntity(*getTokens());
    setIsSubExpression(false);

    if (relationalExpression) {
        PairOfArguments arguments{relationalExpression, nullptr}; 
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
            throw SyntaxErrorException("Missing ) token");
        }
        else {
            nextToken();
            PairOfArguments arguments{conditionalExpression, nullptr};
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
        throw SyntaxErrorException("Missing ) token");
    }

    nextToken();
    string operation = getTokenValue();
    if (!(getTokenType() == TokenType::OR || getTokenType() == TokenType::AND)) {
        throw SyntaxErrorException("Missing || or && token");
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
                throw SyntaxErrorException("Missing ) token");
            } else {
                PairOfArguments pairOfArguments{leftConditionalExpression, rightConditionalExpression};
                return make_shared<ConditionalOperation>(operation, pairOfArguments);
            }
        }
        else {
            throw SyntaxErrorException("Missing ( token");
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