#include "IfStatementParser.h"

shared_ptr<Statement> IfStatementParser::parseEntity(Tokens& tokens) {
    checkStartOfIfStatement(tokens);

    shared_ptr<ConditionalOperation> condition = extractCondition(tokens);
    auto ifStatement =
        make_shared<IfStatement>(Program::getAndIncrementStatementNumber(),
            condition,
            getProcedureName());
    // Erase 'then' and '{' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    while (!tokens.empty() && !isEndOfStatement(tokens)) {
        auto statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(getProcedureName());
        auto statement = statementParser->parseEntity(tokens);
        ifStatement->addThenStatement(statement);
    }

    if (isEndOfStatement(tokens)) {
        // Erase '}' from tokens
        tokens.erase(tokens.begin());
    }

    if (!hasElseStatements(tokens)) {
        throw SyntaxErrorException("If statement is missing an else block");
    }
    
    checkStartOfElseStatement(tokens);
    // Erase 'else' and '{' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);
    while (!tokens.empty() && !isEndOfStatement(tokens)) {
        auto statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(getProcedureName());
        auto statement = statementParser->parseEntity(tokens);
        ifStatement->addElseStatement(statement);
    }

    if (isEndOfStatement(tokens)) {
        // Erase '}' from tokens
        tokens.erase(tokens.begin());
    }

    return ifStatement;
}

shared_ptr<ConditionalOperation> IfStatementParser::extractCondition(Tokens& tokens) {
    Tokens conditionTokens;

    // Erase 'if and (' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    auto end = find_if(tokens.begin(), tokens.end(), [](const shared_ptr<Token>& token) {
        return token->getType() == TokenType::LEFT_BRACE;
        });

    
    if (end == tokens.end()) {
        throw SyntaxErrorException("If statement is missing a {");
    }

    auto token = prev(end);
    if (token->get()->getValue() != "then") {
        throw SyntaxErrorException("If statement is missing a then");
    }

    token = prev(token);
    if (token->get()->getType() != TokenType::RIGHT_PARANTHESIS) {
        throw SyntaxErrorException("If statement condition should be bounded by ( and )");
    }

    for (auto i = tokens.begin(); i != end - 2; ++i) {
        conditionTokens.push_back(*i);
    }

    // Erasing all condition tokens and ) from tokens
    tokens.erase(tokens.begin(), end - 1);
    auto expressionParser =
        ExpressionParserFactory::getExpressionParser(conditionTokens, EntityType::If);
    auto
        condition = (expressionParser->parseEntity(
            conditionTokens));
    if (!condition) {
        throw SyntaxErrorException("Invalid condition for if statement");
    }

    return dynamic_pointer_cast<ConditionalOperation>(condition);
}

void IfStatementParser::checkStartOfIfStatement(Tokens& tokens) const {
    if (tokens[0]->getValue() != "if") {
        throw SyntaxErrorException("Missing if statement");
    }

    if (tokens[1]->getType() != TokenType::LEFT_PARANTHESIS) {
        throw SyntaxErrorException("Missing ( at the start of if block");
    }
}

void IfStatementParser::checkStartOfElseStatement(Tokens& tokens) const {
    if (tokens[0]->getValue() != "else") {
        throw SyntaxErrorException("Missing else statement");
    }

    if (tokens[1]->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("Missing { at the start of else block");
    }
}

bool IfStatementParser::hasElseStatements(Tokens& tokens) const {
    return tokens[0]->getValue() == "else";
}

bool IfStatementParser::isEndOfStatement(Tokens& tokens) const {
    return tokens[0]->getType() == TokenType::RIGHT_BRACE;
}