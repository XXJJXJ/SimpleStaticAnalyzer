#include "AssignStatementParser.h"

shared_ptr<Statement> AssignStatementParser::parseEntity(vector<shared_ptr<Token>>& tokens) {
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
        ExpressionParserFactory::getExpressionParser(expressionTokens, "assign");
    auto expression = expressionParser->parseEntity(expressionTokens);
    assignStatement->addExpression(expression);
    checkEndOfStatement(tokens);
    // Erase ';' from tokens
    tokens.erase(tokens.begin());
    return assignStatement;
}

string AssignStatementParser::extractVariableName(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Missing variable in Assign statement");
    }

    if (tokens[1]->getValue() != "=") {
        throw SyntaxErrorException("Missing = in Assign statement");
    }

    return tokens[0]->getValue();
}

vector<shared_ptr<Token>> AssignStatementParser::extractExpression(vector<shared_ptr<Token>>& tokens) const {
    vector<shared_ptr<Token>> expressionTokens;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[0]->getValue() == ";") {
            break;
        }
        else {
            expressionTokens.push_back(tokens[0]);
            tokens.erase(tokens.begin());
        }
    }

    return expressionTokens;
}

void AssignStatementParser::checkEndOfStatement(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getValue() != ";") {
        throw SyntaxErrorException("Assign statement does not end with ;");
    }
}