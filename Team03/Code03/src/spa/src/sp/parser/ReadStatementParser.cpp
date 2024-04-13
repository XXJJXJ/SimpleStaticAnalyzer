#include "ReadStatementParser.h"

shared_ptr<Statement> ReadStatementParser::parseEntity(Tokens &tokens) {
    string variableName = extractVariableName(tokens);
    shared_ptr<Variable> variable = make_shared<Variable>(variableName);
    shared_ptr<ReadStatement> readStatement =
        make_shared<ReadStatement>(Program::getAndIncrementStatementNumber(), variable, getProcedureName());
    return readStatement;
}

string ReadStatementParser::extractVariableName(Tokens &tokens) const {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    shared_ptr<Token> token2 = tokens[2];

    if (token0->getValue() != "read") {
        throw SyntaxErrorException("Missing read name token in Read statement");
    } else if (token1->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Missing variable name token in Read statement");
    } else if (token2->getType() != TokenType::SEMICOLON) {
        throw SyntaxErrorException("Missing ; token in Read statement");
    }

    // Erase 'read variable;' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 3);
    return token1->getValue();
}