#include "IfStatementParser.h"

shared_ptr<Statement> IfStatementParser::parseEntity(Tokens& tokens) {
    checkStartOfIfStatement(tokens);

    // Erase 'if' and '(' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);
    auto condition = extractCondition(tokens);
    auto ifStatement =
        make_shared<IfStatement>(Program::getAndIncrementStatementNumber(),
            condition,
            getProcedureName());

    parseBlock("then", ifStatement, tokens);
    if (ifStatement->getThenStatementList().size() == 0) {
        throw SyntaxErrorException("If statement's then block cannot be empty");
    }
    parseBlock("else", ifStatement, tokens);
    if (ifStatement->getElseStatementList().size() == 0) {
        throw SyntaxErrorException("If statement's else block cannot be empty");
    }

    return ifStatement;
}

void IfStatementParser::parseBlock(string value, shared_ptr<IfStatement> ifStatement, Tokens& tokens) {
    checkStartOfBlock(value, tokens);
    // Erase 'then'/'else' and '{' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    while (!tokens.empty() && !isEndOfStatement(tokens)) {
        auto statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(getProcedureName());
        auto statement = statementParser->parseEntity(tokens);
        if (value == "then") {
            ifStatement->addThenStatement(statement);
        } 
        else {
            ifStatement->addElseStatement(statement);
        }
    }

    if (isEndOfStatement(tokens)) {
        // Erase '}' from tokens
        tokens.erase(tokens.begin());
    }
    else {
        throw SyntaxErrorException("If statement's then block is missing a }");
    }
}

shared_ptr<ConditionalOperation> IfStatementParser::extractCondition(Tokens& tokens) {
    Tokens conditionTokens;
    auto end = checkConditionOfIfStatement(tokens);

    for (auto i = tokens.begin(); i != end - 2; ++i) {
        conditionTokens.push_back(*i);
    }

    // Erasing all condition tokens and ')' from tokens
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

void IfStatementParser::checkStartOfBlock(string value, Tokens& tokens) const {
    if (tokens[0]->getValue() != value) {
        throw SyntaxErrorException("Missing " + value + " block");
    }

    if (tokens[1]->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("Missing { at the start of " + value + " then block");
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