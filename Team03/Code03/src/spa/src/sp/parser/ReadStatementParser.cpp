#include "ReadStatementParser.h"

shared_ptr<Statement> ReadStatementParser::parseEntity(vector<shared_ptr<Token>>& tokens) {
    string variableName = extractVariableName(tokens);
    auto variable = make_shared<Variable>(variableName);
    auto readStatement =
        make_shared<ReadStatement>(
            Program::getAndIncrementStatementNumber(), 
            variable,
            getProcedureName());
    return readStatement;
}

std::string ReadStatementParser::extractVariableName(vector<shared_ptr<Token>>& tokens) const {
    shared_ptr<Token> token0 = tokens[0];
    shared_ptr<Token> token1 = tokens[1];
    shared_ptr<Token> token2 = tokens[2];

    if (token0->getValue() != "read") {
        throw SyntaxErrorException("Read statement should start with read keyword");
    }

    else if (token1->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Read statement does not have a variable");
    }

    else if (token2->getType() != TokenType::SEMICOLON) {
        throw SyntaxErrorException("Read statement should end with a ;");
    }

    tokens.erase(tokens.begin(), tokens.begin() + 3);
    return token1->getValue();
}