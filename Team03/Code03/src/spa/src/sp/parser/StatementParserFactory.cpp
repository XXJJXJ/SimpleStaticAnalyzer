#include "StatementParserFactory.h"

shared_ptr<StatementParser> StatementParserFactory::getStatementParser(vector<shared_ptr<Token>>& tokens) {
    if (checkKeywordType(tokens, "print", false)) {
        return make_shared<PrintStatementParser>();
    }
    else if (checkKeywordType(tokens, "read", false)) {
        return make_shared<ReadStatementParser>();
    }
    else if (checkKeywordType(tokens, "if", true)) {
        return make_shared<IfStatementParser>();
    }
    else if (checkKeywordType(tokens, "while", true)) {
        return make_shared<WhileStatementParser>();
    } 
    else if (checkKeywordType(tokens, "assign", false)) {
        return make_shared<AssignStatementParser>();
    }
    throw SemanticErrorException("Unknown Statement Type");
}

bool StatementParserFactory::checkKeywordType(
    vector<shared_ptr<Token>>& tokens,
    string statementType,
    bool hasParenthesis) {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];

    return 
        (!hasParenthesis && token0->getValue() == statementType && token1->getType() == TokenType::NAME) ||
        (hasParenthesis && token0->getValue() == statementType && token1->getType() == TokenType::LEFT_PARENTHESIS) ||
        (!hasParenthesis && token0->getType() == TokenType::NAME && token1->getValue() == "=");
}