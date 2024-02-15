#include "StatementParserFactory.h"

shared_ptr<StatementParser> StatementParserFactory::getStatementParser(vector<shared_ptr<Token>> tokens) {
    if (checkKeywordType(tokens, "print")) {
        return make_shared<PrintStatementParser>();
    }
    else if (checkKeywordType(tokens, "read")) {
        return make_shared<ReadStatementParser>();
    }
    else if (checkKeywordType(tokens, "if")) {
        //return make_shared<IfStatementParser>();
    }
    else if (checkKeywordType(tokens, "while")) {
        //return make_shared<WhileStatementParser>();
    } 
    else if (checkKeywordType(tokens, "assign")) {
        //return make_shared<AssignStatementParser>();
    }
    throw SemanticErrorException("Unknown Statement Type");
}

bool StatementParserFactory::checkKeywordType(
    vector<shared_ptr<Token>> tokens,
    string statementType) {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];

    return 
        (token0->getValue() == statementType && token1->getType() == TokenType::NAME) || 
        (token0->getValue() == statementType && token1->getType() == TokenType::LEFT_PARANTHESIS) ||
        (token0->getType() == TokenType::NAME && token1->getValue() == "=");
}