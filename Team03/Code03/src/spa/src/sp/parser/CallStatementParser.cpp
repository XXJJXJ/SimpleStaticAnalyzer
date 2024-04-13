#include "CallStatementParser.h"

shared_ptr<Statement> CallStatementParser::parseEntity(Tokens &tokens) {
    string procedureName = extractProcedureName(tokens);
    shared_ptr<Procedure> procedure = make_shared<Procedure>(procedureName);
    shared_ptr<CallStatement> callStatement =
        make_shared<CallStatement>(
            Program::getAndIncrementStatementNumber(),
            procedure,
            getProcedureName());
    return callStatement;
}

string CallStatementParser::extractProcedureName(Tokens &tokens) const {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    shared_ptr<Token> token2 = tokens[2];

    if (token0->getValue() != "call") {
        throw SyntaxErrorException("Missing call name token in Call statement");
    } else if (token1->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Missing name token in Call statement");
    } else if (token2->getType() != TokenType::SEMICOLON) {
        throw SyntaxErrorException("Missing ; token in Call statement");
    }

    // Erase 'call Procedure;' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 3);
    return token1->getValue();
}