#include "StatementParserFactory.h"
#include <sp/parser/CallStatementParser.h>

shared_ptr<StatementParser> StatementParserFactory::getStatementParser(Tokens &tokens) {
    if (tokens.size() < 2) {
        throw SyntaxErrorException("Insufficient number of tokens");
    } else {
        if (checkAssignment(tokens)) {
            return make_shared<AssignStatementParser>();
        } else if (checkKeywordType(tokens, "if", true)) {
            return make_shared<IfStatementParser>();
        } else if (checkKeywordType(tokens, "while", true)) {
            return make_shared<WhileStatementParser>();
        } else if (checkKeywordType(tokens, "print", false)) {
            return make_shared<PrintStatementParser>();
        } else if (checkKeywordType(tokens, "read", false)) {
            return make_shared<ReadStatementParser>();
        } else if (checkKeywordType(tokens, "call", false)) {
            return make_shared<CallStatementParser>();
        } else {
            throw SemanticErrorException("Unknown Statement Type");
        }
    }
}

bool StatementParserFactory::checkKeywordType(Tokens &tokens, string statementType, bool hasParenthesis) {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    return (hasParenthesis && token0->getValue() == statementType && token1->getType() == TokenType::LEFT_PARANTHESIS)
        || (!hasParenthesis && token0->getValue() == statementType && token1->getType() == TokenType::NAME);
}

bool StatementParserFactory::checkAssignment(Tokens &tokens) {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    return token0->getType() == TokenType::NAME && token1->getType() == TokenType::SINGLE_EQUAL;
}