#include "StatementParserFactory.h"

shared_ptr<StatementParser> StatementParserFactory::getStatementParser(vector<shared_ptr<Token>>& tokens) {
    if (checkKeywordType(tokens, "if", true)) {
        return make_shared<IfStatementParser>();
    }
    else if (checkKeywordType(tokens, "while", true)) {
        return make_shared<WhileStatementParser>();
    }
    else if (checkAssignment(tokens)) {
        return make_shared<AssignStatementParser>();
    }
    else if (checkKeywordType(tokens, "print", false)) {
        return make_shared<PrintStatementParser>();
    }
    else if (checkKeywordType(tokens, "read", false)) {
        return make_shared<ReadStatementParser>();
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
        (hasParenthesis && token0->getValue() == statementType && token1->getValue() == "(") ||
        (!hasParenthesis && token0->getValue() == statementType && token1->getType() == TokenType::NAME);
}

bool StatementParserFactory::checkAssignment(vector<shared_ptr<Token>>& tokens) {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    return 
        token0->getType() == TokenType::NAME && 
        token1->getValue() == "=";
}