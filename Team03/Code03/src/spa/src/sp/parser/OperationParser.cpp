#include "OperationParser.h"

void OperationParser::getNext() {
    if (*indexPointer < tokens.size()) {
        token = tokens[*indexPointer];
        tokenValue = token->getValue();
        (*isProcessedTokenPointer) = false;
        (*indexPointer)++;
    }
}

bool OperationParser::isEndOfStatement() {
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

void OperationParser::updateToken() {
    token = tokens[static_cast<size_t>(*indexPointer) - 1];
    tokenValue = token->getValue();
}

int OperationParser::getIndex() {
    return (*indexPointer) - 1;
}

shared_ptr<int> OperationParser::getIndexPointer() {
    return indexPointer;
}

shared_ptr<Expression> OperationParser::parseEntity(vector<shared_ptr<Token>>& tokens) {
    setup(tokens);
    shared_ptr<Expression> result = parse();
    validateForBalancedParenthesis();
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

void OperationParser::setup(vector<shared_ptr<Token>>& tokens_) {
    if (*indexPointer == 0) {
        tokens = tokens_;
        getNext();
    }

    if (isInheritArguments) {
        tokens = tokens_;
        token = tokens[static_cast<size_t>(*indexPointer) - 1];
        tokenValue = token->getValue();
    }
}

void OperationParser::inheritArguments(shared_ptr<int> index, bool isSubExpression_, shared_ptr<bool> isProcessedToken) {
    isInheritArguments = true;
    indexPointer = index;
    isSubExpression = isSubExpression_;
    isProcessedTokenPointer = isProcessedToken;
}

void OperationParser::addParenthesis(TokenType type, string value, int index_) {
    if (parenthesesIndexMappings.find(index_) != parenthesesIndexMappings.end()) {
        return;
    }

    parenthesesIndexMappings[index_] = value;
    if (value == "(") {
        parenthesesContainer.push(value);
    }
    else if (value == ")") {
        parenthesesContainer.pop();
    }
}

void OperationParser::validateForBalancedParenthesis() {
    if (isSubExpression || (isEndOfStatement() && *isProcessedTokenPointer && parenthesesContainer.empty())) {
        return;
    }
    throw SyntaxErrorException("Unbalanced parenthesis ()");
}

void OperationParser::validateEnoughTokensToProcess() {
    if (*isProcessedTokenPointer) {
        throw SyntaxErrorException("Insufficient tokens to process");
    }
}