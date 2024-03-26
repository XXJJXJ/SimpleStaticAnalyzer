#include "OperationParser.h"

TokenType OperationParser::getTokenType() {
    markTokenAsProcessed();
    return token->getType();
}

string OperationParser::getTokenValue() {
    markTokenAsProcessed();
    return token->getValue();
}

shared_ptr<int> OperationParser::getIndexPointer() {
    return indexPointer;
}

shared_ptr<bool> OperationParser::getIsProcessedTokenPointer() {
    return isProcessedTokenPointer;
}

shared_ptr<bool> OperationParser::getIsSubExpressionPointer() {
    return isSubExpressionPointer;
}

shared_ptr<Tokens> OperationParser::getTokens() {
    return make_shared<Tokens>(tokens);
}

shared_ptr<Expression> OperationParser::parseEntity(Tokens& tokens) {
    if (*indexPointer == 0) {
        initialiseTokens(tokens);
    }
    if (*isSetPairOfArgumentsPointer) {
        setTokens(tokens);
    }
    shared_ptr<Expression> expression = parse();
    checkParentheses();
    return expression;
}

bool OperationParser::isEndOfTokens() {
    return *indexPointer == tokens.size();
}

void OperationParser::nextToken() {
    if (hasMoreTokens()) {
        *isProcessedTokenPointer = false;
        token = tokens[*indexPointer];
        incrementIndex();
    }
}

void OperationParser::setNextToken() {
    token = tokens[static_cast<size_t>(*indexPointer) - 1];
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

void OperationParser::setIsSubExpression(bool isSubExpression) {
    *isSubExpressionPointer = isSubExpression;
}

void OperationParser::setPairOfArguments(shared_ptr<bool> isSubExpressionPointer_, shared_ptr<int> indexPointer_,  shared_ptr<bool> isProcessedTokenPointer_) {
    *isSetPairOfArgumentsPointer = true;
    isSubExpressionPointer = isSubExpressionPointer_;
    indexPointer = indexPointer_;
    isProcessedTokenPointer = isProcessedTokenPointer_;
}

bool OperationParser::hasMoreTokens() {
    return *indexPointer < tokens.size();
}

void OperationParser::incrementIndex() {
    (*indexPointer)++;
}

void OperationParser::markTokenAsProcessed() {
    *isProcessedTokenPointer = true;
}

void OperationParser::initialiseTokens(Tokens& tokens_) {
    tokens = tokens_;
    nextToken();
}

void OperationParser::setTokens(Tokens& tokens_) {
    tokens = tokens_;
    setNextToken();
}

void OperationParser::checkParentheses() {
    if (!*isSubExpressionPointer && !(parentheses.empty() && isEndOfTokens() && *isProcessedTokenPointer)) {
        throw SyntaxErrorException("Unbalanced parenthesis in procedure");
    }
}