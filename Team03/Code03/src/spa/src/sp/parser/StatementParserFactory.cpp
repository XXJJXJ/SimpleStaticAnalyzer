#include "StatementParserFactory.h"

shared_ptr<StatementParser> StatementParserFactory::getStatementParser(vector<shared_ptr<Token>> tokens) {
    auto line = tokens.front();
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
    string_view statementType) {
    shared_ptr<Token> token = tokens[0];

    if (token->getValue() != statementType) {
        throw SyntaxErrorException("Invalid statement");
    }
    
    return true;
}