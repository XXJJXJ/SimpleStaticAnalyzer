#include "OperationParser.h"

void OperationParser::getNextToken() {
    if (*indexPointer < tokens.size()) {
        token = tokens[*indexPointer];
        tokenValue = token->getValue();
        (*indexPointer)++;
        (*isProcessedTokenPointer) = false;
    }
}

bool OperationParser::isEndOfTokens() {
    return *indexPointer == tokens.size();
}

TokenType OperationParser::getTokenType() {
    (*isProcessedTokenPointer) = true;
    return token->getType();
}

string OperationParser::getTokenValue() {
    (*isProcessedTokenPointer) = true;
    return tokenValue;
}

shared_ptr<ExpressionParser::Tokens> OperationParser::getTokens() {
    return make_shared<ExpressionParser::Tokens>(tokens);
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
    shared_ptr<Expression> result = parse();
    validateParenthesis();
    return result;
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
        getNextToken();
    }

    if (isSetArguments) {
        tokens = tokens_;
        token = tokens[static_cast<size_t>(*indexPointer) - 1];
        tokenValue = token->getValue();
    }
}

void OperationParser::setArguments(shared_ptr<int> index, bool isSubExpression_, shared_ptr<bool> isProcessedToken) {
    indexPointer = index;
    isSetArguments = true;
    isSubExpression = isSubExpression_;
    isProcessedTokenPointer = isProcessedToken;
}

void OperationParser::addParenthesis(TokenType tokenType, int index_) {
    if (parenthesesToIndexMap.find(index_) != parenthesesToIndexMap.end()) {
        return;
    }
    else {
        parenthesesToIndexMap[index_] = tokenType;
        if (tokenType == TokenType::LEFT_PARANTHESIS) {
            parenthesesStorage.push(tokenType);
        }
        else if (tokenType == TokenType::RIGHT_PARANTHESIS) {
            parenthesesStorage.pop();
        }
    }
}

void OperationParser::validateParenthesis() {
    if (isSubExpression || (parenthesesStorage.empty() && isEndOfTokens() && *isProcessedTokenPointer)) {
        return;
    } 
    else {
        throw SyntaxErrorException("Procedure contains unbalanced parenthesis");
    }
}

void OperationParser::validateTokens() {
    if (*isProcessedTokenPointer) {
        throw SyntaxErrorException("Insufficient tokens for processing");
    }
}