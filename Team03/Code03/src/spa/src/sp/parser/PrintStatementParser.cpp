#include "PrintStatementParser.h"

shared_ptr<Statement> PrintStatementParser::parseEntity(vector<shared_ptr<Token>> tokens) {
    string variableName = extractVariableName(tokens);
    auto variable = make_shared<Variable>(variableName);
    auto printStatement =
        make_shared<PrintStatement>(
            Program::getAndIncrementStatementNumber(),
            variable,
            getProcedureName());
    return printStatement;
}

std::string PrintStatementParser::extractVariableName(vector<shared_ptr<Token>> tokens) const {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    shared_ptr<Token> token2 = tokens[2];

    if (token0->getValue() != "read") {
        throw SyntaxErrorException("Read statement should start with print keyword");
    }

    else if (token1->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Print statement does not have a variable");
    }

    else if (token2->getType() != TokenType::SEMICOLON) {
        throw SyntaxErrorException("Print statement should end with a ;");
    }

    return token1->getValue();
}