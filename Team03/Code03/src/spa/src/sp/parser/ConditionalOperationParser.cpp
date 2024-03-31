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

    return parseExpression(index, getTokenType());
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

    return nullptr;
}

shared_ptr<Expression> ConditionalOperationParser::parseExpression(int index, TokenType tokenType) {
    setPairOfArguments(
        getIsSubExpressionPointer(),
        make_shared<int>(index),
        getIsProcessedTokenPointer());
    if (tokenType == TokenType::NOT) {
        return parseSubExpression("!", nullptr);
    }
    else if (tokenType == TokenType::LEFT_PARANTHESIS) {
        nextToken();
        setIsSubExpression(true);
        return parseAndOrSubExpression();
    }
    else {
        throw SyntaxErrorException("Invalid Conditional expression");
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseSubExpression(string operation, shared_ptr<Expression> subExpression) {
    nextToken();
    if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        setIsSubExpression(true);
        nextToken();
        shared_ptr<Expression> subExpression_ = parse();
        if (subExpression) {
            nextToken();
        }
        if (getTokenType() == TokenType::RIGHT_PARANTHESIS) {
            PairOfArguments pairOfArguments;
            subExpression
                ? pairOfArguments = {subExpression, subExpression_}
                : (nextToken(), pairOfArguments = {subExpression_, subExpression});
            return make_shared<ConditionalOperation>(operation, pairOfArguments);
        }

        throw SyntaxErrorException("Missing ) token in Conditional expression");
    }

    throw SyntaxErrorException("Missing ( token in Conditional expression");

}

shared_ptr<Expression> ConditionalOperationParser::parseAndOrSubExpression() {
    shared_ptr<Expression> leftSubExpression = parse();
    if (getTokenType() == TokenType::RIGHT_PARANTHESIS) {
        nextToken();
        string operation = getTokenValue();
        if (getTokenType() == TokenType::OR || getTokenType() == TokenType::AND) {
            return parseSubExpression(operation, leftSubExpression);
        }
        
        throw SyntaxErrorException("Missing || or && token in Conditional expression");

    }

    throw SyntaxErrorException("Missing ) token in Conditional expression");
}