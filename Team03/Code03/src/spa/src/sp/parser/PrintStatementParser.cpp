#include "PrintStatementParser.h"

shared_ptr<Statement> PrintStatementParser::parseEntity(Tokens &tokens) {
    string variableName = extractVariableName(tokens);
    shared_ptr<Variable> variable = make_shared<Variable>(variableName);
    shared_ptr<PrintStatement> printStatement =
        make_shared<PrintStatement>(
            Program::getAndIncrementStatementNumber(),
            variable,
            getProcedureName());
    return printStatement;
}

string PrintStatementParser::extractVariableName(Tokens &tokens) const {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    shared_ptr<Token> token2 = tokens[2];

    if (token0->getValue() != "print") {
        throw SyntaxErrorException("Missing print name token in Print statement");
    } else if (token1->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Missing variable name token in Print statement");
    } else if (token2->getType() != TokenType::SEMICOLON) {
        throw SyntaxErrorException("Missing ; token in Print statement");
    }

    // Erase 'print variable;' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 3);
    return token1->getValue();
}