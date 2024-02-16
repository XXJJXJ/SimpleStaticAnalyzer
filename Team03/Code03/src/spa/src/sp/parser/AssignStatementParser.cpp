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

    checkEndOfStatement(tokens);
    // Erase ';' from tokens
    tokens.erase(tokens.begin());
    auto expressionTokens = extractExpression(tokens);
    auto expressionParser =
        ExpressionParserFactory::getExpressionParser(expressionTokens, "assign");
    auto expression = expressionParser->parseEntity(expressionTokens);
    assignStatement->addExpression(expression);
    return assignStatement;
}

string AssignStatementParser::extractVariableName(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Missing variable in Assign statement");
    }

    if (tokens[1]->getType() != TokenType::SINGLE_EQUAL) {
        throw SyntaxErrorException("Missing = in Assign statement");
    }

    return tokens[0]->getValue();
}

vector<shared_ptr<Token>> AssignStatementParser::extractExpression(vector<shared_ptr<Token>>& tokens) const {
    vector<shared_ptr<Token>> expressionTokens;

    auto end = find_if(tokens.begin(), tokens.end(), [](const shared_ptr<Token>& token) {
        return token->getType() == TokenType::SEMICOLON;
        });

    for (auto i = tokens.begin(); i != end; ++i) {
        expressionTokens.push_back(*i);
        // Erase 'expression' from tokens
        tokens.erase(i);
    }

    return expressionTokens;
}

void AssignStatementParser::checkEndOfStatement(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getType() != TokenType::SEMICOLON) {
        throw SyntaxErrorException("Assign statement does not end with ;");
    }
}