#include "OperationParser.h"

void OperationParser::nextToken() {
    if (hasMoreTokens()) {
        token = tokens[*indexPointer];
        tokenValue = token->getValue();
        (*isProcessedTokenPointer) = false;
        incrementIndex();
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
    (*isProcessedTokenPointer) = true;
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

void OperationParser::updateNextToken() {
    token = tokens[static_cast<size_t>(*indexPointer) - 1];
    tokenValue = token->getValue();
}

int OperationParser::getIndex() {
    return (*indexPointer) - 1;
}

shared_ptr<int> OperationParser::getIndexPointer() {
    return indexPointer;
}

shared_ptr<Expression> OperationParser::parseEntity(Tokens& tokens) {
    setup(tokens);
    shared_ptr<Expression> expression = parse();
    checkParentheses();
    return expression;
}

bool OperationParser::getIsProcessedToken() {
    return isProcessedToken;
}

shared_ptr<bool> OperationParser::getIsProcessedTokenPointer() {
    return isProcessedTokenPointer;
}

bool OperationParser::getIsSubExpression() {
    return isSubExpression;
}

void OperationParser::setIsSubExpression(bool isSubExpression_) {
    isSubExpression = isSubExpression_;
}

void OperationParser::setup(Tokens& tokens_) {
    if (*indexPointer == 0) {
        tokens = tokens_;
        nextToken();
    }

    if (isSetArguments) {
        tokens = tokens_;
        updateNextToken();
    }
}

void OperationParser::setArguments(shared_ptr<int> indexPointer_, bool isSubExpression_, shared_ptr<bool> isProcessedTokenPointer_) {
    indexPointer = indexPointer_;
    isSubExpression = isSubExpression_;
    isProcessedTokenPointer = isProcessedTokenPointer_;
    isSetArguments = true;
}

void OperationParser::manageParentheses(TokenType tokenType, int index_) {
    if (parenthesesIndexMap.find(index_) == parenthesesIndexMap.end()) {
        parenthesesIndexMap[index_] = tokenType;
        modifyParentheses(tokenType);
    }
}

void OperationParser::modifyParentheses(TokenType tokenType) {
    if (tokenType == TokenType::LEFT_PARANTHESIS) {
        parentheses.push(tokenType);
    } else if (!parentheses.empty() && tokenType == TokenType::RIGHT_PARANTHESIS) {
        parentheses.pop();
    }
}

void OperationParser::checkParentheses() {\
    if (!isSubExpression && !(parentheses.empty() && isEndOfTokens() && *isProcessedTokenPointer)) {
        throw SyntaxErrorException("Procedure contains unbalanced parenthesis");
    }
}

void OperationParser::checkTokens() {
    if (*isProcessedTokenPointer) {
        throw SyntaxErrorException("Insufficient tokens");
    }
}