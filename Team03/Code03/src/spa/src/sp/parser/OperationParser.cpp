#include "OperationParser.h"

void OperationParser::getNextToken() {
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

shared_ptr<Expression> OperationParser::parseEntity(vector<shared_ptr<Token>>& tokens) {
    setup(tokens);
    shared_ptr<Expression> result = parse();
    validateBalancedParenthesis();
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
        getNextToken();
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

void OperationParser::addParenthesis(string value, int index_) {
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

void OperationParser::validateBalancedParenthesis() {
    if (isSubExpression || (isEndOfStatement() && *isProcessedTokenPointer && parenthesesContainer.empty())) {
        return;
    }
    throw SyntaxErrorException("Procedure contains unbalanced parenthesis");
}

void OperationParser::validateTokensToProcess() {
    if (*isProcessedTokenPointer) {
        throw SyntaxErrorException("Insufficient tokens for processing");
    }
}