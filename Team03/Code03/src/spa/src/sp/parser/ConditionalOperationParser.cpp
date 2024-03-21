#include "ConditionalOperationParser.h"

shared_ptr<Expression> ConditionalOperationParser::parse() {
    index = *getIndexPointer();
    isSubExpression = getIsSubExpression();
    isProcessedToken = *getIsProcessedTokenPointer();

    try {
        shared_ptr<Expression> relationalExpression = parseRelationalOperation();
        if (relationalExpression) {
            return relationalExpression;
        }
    }
    catch (SpaException& e) {
        string check = "Initial parsing of Relational Operation failed";
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
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
        arguments.first = relationalExpression; 
        updateNextToken();
        return make_shared<ConditionalOperation>("relationalExpression", arguments);
    }

    return nullptr;
}

shared_ptr<Expression> ConditionalOperationParser::parseNotOperation() {
    getNextToken();
    if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        getNextToken();
        setIsSubExpression(true);
        shared_ptr<Expression> conditionalExpression = parse();
        if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
            throw SyntaxErrorException("Missing ) in Conditional expression");
        }

        getNextToken();
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
        arguments.first = conditionalExpression;
        return make_shared<ConditionalOperation>("!", arguments);
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseAndOrOperation() {
    getNextToken();
    validateTokens();
    setIsSubExpression(true);
    shared_ptr<Expression> leftConditionalExpression = parse();
    if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
        throw SyntaxErrorException("Missing ) in Conditional expression");
    }

    getNextToken();
    string operation = getTokenValue();
    if (!(getTokenType() == TokenType::AND || getTokenType() == TokenType::OR)) {
        throw SyntaxErrorException("Missing && or || in Conditional expression");
    }
    getNextToken();

    if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        getNextToken();
        setIsSubExpression(true);
        shared_ptr<Expression> rightConditionalExpression = parse();
        if (*(getIndexPointer().get()) < getTokens()->size()) {
            getNextToken();
        }
        if (getTokenType() != TokenType::RIGHT_PARANTHESIS) {
            throw SyntaxErrorException("Missing ) in Conditional expression");
        }
        pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
        arguments.first = leftConditionalExpression;
        arguments.second = rightConditionalExpression;
        return make_shared<ConditionalOperation>(operation, arguments);
    }
    else {
        throw SyntaxErrorException("Missing ( in Conditional Expression");
    }
}

shared_ptr<Expression> ConditionalOperationParser::parseSubExpression() {
    if (getTokenType() == TokenType::NOT) {
        return parseNotOperation();
    }
    else if (getTokenType() == TokenType::LEFT_PARANTHESIS) {
        return parseAndOrOperation();
    }

    throw SyntaxErrorException("Invalid Conditional Operation");
}