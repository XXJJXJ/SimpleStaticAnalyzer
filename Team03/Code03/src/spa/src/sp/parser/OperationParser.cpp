#include "OperationParser.h"

void OperationParser::nextToken() {
    if (hasMoreTokens()) {
        *isProcessedTokenPointer = false;
        token = tokens[*indexPointer];
        tokenValue = token->getValue();
        incrementIndex();
    }
}

void OperationParser::setNextToken() {
    token = tokens[static_cast<size_t>(*indexPointer) - 1];
    tokenValue = token->getValue();
}

void OperationParser::setTokens(Tokens& tokens_) {
    if (*indexPointer == 0) {
        tokens = tokens_;
        nextToken();
    }

    if (*isSetPairOfArgumentsPointer) {
        tokens = tokens_;
        setNextToken();
    }
}

bool OperationParser::hasMoreTokens() {
    return *indexPointer < tokens.size();
}

void OperationParser::incrementIndex() {
    (*indexPointer)++;
}

bool OperationParser::isEndOfTokens() {
    return *indexPointer == tokens.size();
}

void OperationParser::markTokenAsProcessed() {
    *isProcessedTokenPointer = true;
}

TokenType OperationParser::getTokenType() {
    markTokenAsProcessed();
    return token->getType();
}

string OperationParser::getTokenValue() {
    markTokenAsProcessed();
    return tokenValue;
}

shared_ptr<Tokens> OperationParser::getTokens() {
    return make_shared<Tokens>(tokens);
}

int OperationParser::getIndex() {
    return *indexPointer - 1;
}

shared_ptr<int> OperationParser::getIndexPointer() {
    return indexPointer;
}

shared_ptr<Expression> OperationParser::parseEntity(Tokens& tokens) {
    setTokens(tokens);
    shared_ptr<Expression> expression = parse();
    checkParentheses();
    return expression;
}

shared_ptr<bool> OperationParser::getIsProcessedTokenPointer() {
    return isProcessedTokenPointer;
}

bool OperationParser::getIsSubExpression() {
    return *isSubExpressionPointer;
}

void OperationParser::setIsSubExpression(bool isSubExpression) {
    *isSubExpressionPointer = isSubExpression;
}

void OperationParser::setPairOfArguments(bool isSubExpression, shared_ptr<int> indexPointer_,  shared_ptr<bool> isProcessedTokenPointer_) {
    *isSetPairOfArgumentsPointer = true;
    *isSubExpressionPointer = isSubExpression;
    indexPointer = indexPointer_;
    isProcessedTokenPointer = isProcessedTokenPointer_;
}

void OperationParser::manageParentheses(TokenType tokenType) {
    if (tokenType == TokenType::LEFT_PARANTHESIS) {
        parentheses.push(tokenType);
    } 
    else if (!parentheses.empty() && tokenType == TokenType::RIGHT_PARANTHESIS) {
        parentheses.pop();
    }
    else {
        throw SyntaxErrorException("Unbalanced parenthesis in procedure");
    }
}

void OperationParser::checkParentheses() {
    if (!*isSubExpressionPointer && !(parentheses.empty() && isEndOfTokens() && *isProcessedTokenPointer)) {
        throw SyntaxErrorException("Unbalanced parenthesis in procedure");
    }
}