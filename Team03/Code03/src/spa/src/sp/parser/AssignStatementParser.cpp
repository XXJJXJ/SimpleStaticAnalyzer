#include "AssignStatementParser.h"

shared_ptr<Statement> AssignStatementParser::parseEntity(Tokens& tokens) {
    string variableName = extractVariableName(tokens);
    // Erase 'variable =' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);
    Variable variable(variableName);
    auto assignStatement =
        make_shared<AssignStatement>(Program::getAndIncrementStatementNumber(),
            variable,
            getProcedureName());
    auto expressionTokens = extractExpression(tokens);
    auto expressionParser =
        ExpressionParserFactory::getExpressionParser(expressionTokens, EntityType::Assign);
    auto expression = expressionParser->parseEntity(expressionTokens);
    assignStatement->addExpression(expression);
    checkEndOfStatement(tokens);
    // Erase ';' from tokens
    tokens.erase(tokens.begin());
    return assignStatement;
}

string AssignStatementParser::extractVariableName(Tokens& tokens) const {
    if (tokens[0]->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Missing variable in Assign statement");
    }

    if (tokens[1]->getValue() != "=") {
        throw SyntaxErrorException("Missing = in Assign statement");
    }

    return tokens[0]->getValue();
}

Tokens AssignStatementParser::extractExpression(Tokens& tokens) const {
    Tokens expressionTokens;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i]->getValue() == ";") {
            tokens.erase(tokens.begin(), tokens.begin() + i);
            break;
        }
        else {
            expressionTokens.push_back(tokens[i]);
        }
    }

    return expressionTokens;
}

void AssignStatementParser::checkEndOfStatement(Tokens& tokens) const {
    if (tokens[0]->getValue() != ";") {
        throw SyntaxErrorException("Assign statement does not end with ;");
    }
}