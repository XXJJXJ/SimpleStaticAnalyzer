#include "StatementParserFactory.h"

shared_ptr<StatementParser> StatementParserFactory::getStatementParser(vector<shared_ptr<Token>> tokens) {
    if (checkKeywordType(tokens, "print")) {
        return make_shared<PrintStatementParser>();
    }
    else if (checkKeywordType(tokens, "read")) {
        return make_shared<ReadStatementParser>();
    }

    throw SemanticErrorException("Unknown Statement type");
}

bool StatementParserFactory::checkKeywordType(
    vector<shared_ptr<Token>> tokens,
    string statementType) {
    shared_ptr<Token> token = tokens[0];

    return token->getValue() == statementType;
}