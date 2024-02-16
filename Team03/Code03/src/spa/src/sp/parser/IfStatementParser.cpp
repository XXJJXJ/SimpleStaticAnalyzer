#include "IfStatementParser.h"

shared_ptr<Statement> IfStatementParser::parseEntity(vector<shared_ptr<Token>>& tokens) {
    checkStartOfIfStatement(tokens);

    shared_ptr<ConditionalOperation> condition = extractCondition(tokens);
    auto ifStatement =
        make_shared<IfStatement>(Program::getAndIncrementStatementNumber(),
            condition,
            getProcedureName());

    checkStartOfThenStatement(tokens);
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

    if (!hasElseStatements(tokens)) return ifStatement;

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

shared_ptr<ConditionalOperation> IfStatementParser::extractCondition(vector<shared_ptr<Token>>& tokens) {
    vector<shared_ptr<Token>> conditionTokens;

    // Erase 'if and (' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    auto end = find_if(tokens.begin(), tokens.end(), [](const std::shared_ptr<Token>& token) {
        return token->getType() == TokenType::LEFT_BRACE;
        });

    if (end == tokens.end()) {
        throw SyntaxErrorException("Condition of an if statement should be bounded by ( and )");
    }

    for (auto i = tokens.begin(); i != end - 1; ++i) {
        conditionTokens.push_back(*i);
        // Erase condition from tokens
        tokens.erase(i);
    }

    // Erase ')' from tokens
    tokens.erase(tokens.begin());

    auto expressionParser =
        ExpressionParserFactory::getExpressionParser(conditionTokens, "if");
    auto
        condition = (expressionParser->parseEntity(
            conditionTokens));

    if (!condition) {
        throw SyntaxErrorException("Invalid condition for if statement");
    }

    return dynamic_pointer_cast<ConditionalOperation>(condition);
}

void IfStatementParser::checkStartOfIfStatement(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getValue() != "if") {
        throw SyntaxErrorException("Missing if statement");
    }

    if (tokens[1]->getType() != TokenType::LEFT_PARENTHESIS) {
        throw SyntaxErrorException("Missing ( at the start of if block");
    }
}

void IfStatementParser::checkStartOfThenStatement(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getValue() != "then") {
        throw SyntaxErrorException("Missing then statement");
    }

    if (tokens[1]->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("Missing { at the start of then block");
    }
}

void IfStatementParser::checkStartOfElseStatement(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getValue() != "else") {
        throw SyntaxErrorException("Missing else statement");
    }

    if (tokens[1]->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("Missing { at the start of else block");
    }
}

bool IfStatementParser::hasElseStatements(vector<shared_ptr<Token>>& tokens) const {
    return find_if(tokens.begin(), tokens.end(),
        [&](shared_ptr<Token> const ptr) {
            return ptr->getValue() == "else";
        }) != tokens.end();
}

bool IfStatementParser::isEndOfStatement(vector<shared_ptr<Token>>& tokens) const {
    return find_if(tokens.begin(), tokens.end(),
        [&](shared_ptr<Token> const ptr) {
            return ptr->getType() == TokenType::RIGHT_BRACE;
        }) != tokens.end();
}