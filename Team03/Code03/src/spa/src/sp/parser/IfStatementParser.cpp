#include "IfStatementParser.h"

shared_ptr<Statement> IfStatementParser::parseEntity(Tokens& tokens) {
    checkStartOfIfStatement(tokens);

    // Erase 'if and (' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);
    auto condition = extractCondition(tokens);
    auto ifStatement =
        make_shared<IfStatement>(Program::getAndIncrementStatementNumber(),
            condition,
            getProcedureName());

    parseThenBlock(ifStatement, tokens);
    parseElseBlock(ifStatement, tokens);

    return ifStatement;
}

void IfStatementParser::parseThenBlock(shared_ptr<IfStatement> ifStatement, Tokens& tokens) {
    checkStartOfThenBlock(tokens);
    // Erase 'then' and '{' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    while (!tokens.empty() && !isEndOfStatement(tokens)) {
        auto statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(getProcedureName());
        auto statement = statementParser->parseEntity(tokens);
        ifStatement->addThenStatement(statement);
    }
    if (ifStatement->getThenStatementList().size() == 0) {
        throw SyntaxErrorException("If statement's then block cannot be empty");
    }

    if (isEndOfStatement(tokens)) {
        // Erase '}' from tokens
        tokens.erase(tokens.begin());
    }
    else {
        throw SyntaxErrorException("If statement's then block is missing a }");
    }
}

void IfStatementParser::parseElseBlock(shared_ptr<IfStatement> ifStatement, Tokens& tokens) {
    checkStartOfElseBlock(tokens);
    // Erase 'else' and '{' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    while (!tokens.empty() && !isEndOfStatement(tokens)) {
        auto statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(getProcedureName());
        auto statement = statementParser->parseEntity(tokens);
        ifStatement->addElseStatement(statement);
    }
    if (ifStatement->getElseStatementList().size() == 0) {
        throw SyntaxErrorException("If statement's else block cannot be empty");
    }

    if (isEndOfStatement(tokens)) {
        // Erase '}' from tokens
        tokens.erase(tokens.begin());
    }
    else {
        throw SyntaxErrorException("If statement's else block is missing a }");
    }
}

shared_ptr<ConditionalOperation> IfStatementParser::extractCondition(Tokens& tokens) {
    Tokens conditionTokens;
    auto end = checkConditionOfIfStatement(tokens);

    for (auto i = tokens.begin(); i != end - 2; ++i) {
        conditionTokens.push_back(*i);
    }

    // Erasing all condition tokens and ) from tokens
    tokens.erase(tokens.begin(), end - 1);
    auto expressionParser = ExpressionParserFactory::getExpressionParser(conditionTokens, EntityType::If);
    auto condition = (expressionParser->parseEntity(conditionTokens));
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

Tokens::iterator IfStatementParser::checkConditionOfIfStatement(Tokens& tokens) const {
    auto end = find_if(tokens.begin(), tokens.end(), [](const shared_ptr<Token>& token) {
        return token->getType() == TokenType::LEFT_BRACE;
        });

    if (end == tokens.end()) {
        throw SyntaxErrorException("If statement is missing a {");
    }

    // 'then' token 
    auto token = prev(end);
    // ')' token
    token = prev(token);
    if (token->get()->getType() != TokenType::RIGHT_PARANTHESIS) {
        throw SyntaxErrorException("If statement condition is not bounded by )");
    }

    return end;
}

void IfStatementParser::checkStartOfThenBlock(Tokens& tokens) const {
    if (tokens[0]->getValue() != "then") {
        throw SyntaxErrorException("Missing then block");
    }

    if (tokens[1]->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("Missing { at the start of then block");
    }
}

void IfStatementParser::checkStartOfElseBlock(Tokens& tokens) const {
    if (tokens[0]->getValue() != "else") {
        throw SyntaxErrorException("If statement is missing else block");
    }

    if (tokens[1]->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("Missing { at the start of else block");
    }
}

bool IfStatementParser::isEndOfStatement(Tokens& tokens) const {
    if (tokens.size() > 0) {
        return tokens[0]->getType() == TokenType::RIGHT_BRACE;
    }
    else {
        return false;
    }
}