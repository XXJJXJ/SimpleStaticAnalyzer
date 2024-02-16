#include "OperationParser.h"

void OperationParser::getNext() {
    if (index < tokens.size()) {
        token = tokens[index];
        tokenValue = token->getValue();
        isProcessedToken = false;
        index++;
    }
}

bool OperationParser::isEndOfStatement() {
    return token->getType() == TokenType::SEMICOLON;
}

TokenType OperationParser::getTokenType() {
    isProcessedToken = true;
    return token->getType();
}

string OperationParser::getTokenValue() {
    isProcessedToken = true;
    return tokenValue;
}

shared_ptr<ExpressionParser::Tokens> OperationParser::getTokens() {
    return make_shared<ExpressionParser::Tokens>(tokens);
}

int OperationParser::getIndex() {
    return index;
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

bool OperationParser::getIsSubExpression() {
    return isSubExpression;
}

void OperationParser::setIsSubExpression(bool isSubExpr) {
    isSubExpression = isSubExpr;
}

void OperationParser::setup(vector<shared_ptr<Token>>& tokens) {
    if (index == 0) {
        getNext();
    }

    if (isInheritArguments) {
        token = tokens[index - 1];
        tokenValue = token->getValue();
    }
}

void OperationParser::updateToken() {
    token = tokens[index - 1];
    tokenValue = token->getValue();
}

void OperationParser::inheritArguments(int i, bool isSubExpr, bool isProcessedT) {
    isInheritArguments = true;
    index = i;
    isSubExpression = isSubExpr;
    isProcessedToken = isProcessedT;
}

void OperationParser::addParenthesis(TokenType type, string value, int index) {
    if (parenthesesIndexMappings.find(index) != parenthesesIndexMappings.end()) {
        return;
    }

    parenthesesIndexMappings[index] = value;
    if (type == TokenType::LEFT_PARENTHESIS) {
        parenthesesContainer.push(value);
    }
    else if (type == TokenType::RIGHT_PARENTHESIS) {
        parenthesesContainer.pop();
    }
}

void OperationParser::validateForBalancedParenthesis() {
    if (isSubExpression || (isEndOfStatement() && isProcessedToken && parenthesesContainer.empty())) {
        return;
    }
    throw SyntaxErrorException("Unbalanced parenthesis ()");
}

void OperationParser::validateEnoughTokensToProcess() {
    if (isProcessedToken) {
        throw SyntaxErrorException("Insufficient tokens to process");
    }
}