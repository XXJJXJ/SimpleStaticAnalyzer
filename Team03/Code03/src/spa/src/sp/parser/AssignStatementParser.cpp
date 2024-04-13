#include "AssignStatementParser.h"

shared_ptr<Statement> AssignStatementParser::parseEntity(Tokens &tokens) {
    string variableName = extractVariableName(tokens);
    // Erase 'variable =' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);
    shared_ptr<Variable> variable = make_shared<Variable>(variableName);
    shared_ptr<AssignStatement> assignStatement =
        make_shared<AssignStatement>(Program::getAndIncrementStatementNumber(),
                                     variable,
                                     getProcedureName());
    Tokens expressionTokens = extractExpression(tokens);
    shared_ptr<ExpressionParser> expressionParser =
        ExpressionParserFactory::getExpressionParser(expressionTokens, EntityType::Assign);
    shared_ptr<Expression> expression = expressionParser->parseEntity(expressionTokens);
    assignStatement->addExpression(expression);
    checkEndOfStatement(tokens);
    // Erase ';' from tokens
    tokens.erase(tokens.begin());
    return assignStatement;
}

string AssignStatementParser::extractVariableName(Tokens &tokens) const {
    if (tokens[0]->getType() != TokenType::NAME) {
        throw SyntaxErrorException("Missing variable name token in Assign statement");
    }

    if (tokens[1]->getType() != TokenType::SINGLE_EQUAL) {
        throw SyntaxErrorException("Missing = token in Assign statement");
    }

    return tokens[0]->getValue();
}

Tokens AssignStatementParser::extractExpression(Tokens &tokens) const {
    Tokens expressionTokens;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i]->getType() == TokenType::SEMICOLON) {
            // Erase expression from tokens
            tokens.erase(tokens.begin(), tokens.begin() + i);
            break;
        } else {
            expressionTokens.push_back(tokens[i]);
        }
    }

    return expressionTokens;
}

void AssignStatementParser::checkEndOfStatement(Tokens &tokens) const {
    if (tokens[0]->getType() != TokenType::SEMICOLON) {
        throw SyntaxErrorException("Missing ; token in Assign statement");
    }
}