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
        throw SyntaxErrorException("Empty If statement's then block");
    }
    parseBlock("else", ifStatement, tokens);
    if (ifStatement->getElseStatementList().size() == 0) {
        throw SyntaxErrorException("Empty If statement's else block");
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
        throw SyntaxErrorException("Missing } token in If statement's " + value + " block");
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
        throw SyntaxErrorException("Invalid condition in If statement");
    }

    return dynamic_pointer_cast<ConditionalOperation>(condition);
}

void IfStatementParser::checkStartOfIfStatement(Tokens& tokens) const {
    if (tokens[0]->getValue() != "if") {
        throw SyntaxErrorException("Missing if name token in If statement");
    }

    if (tokens[1]->getType() != TokenType::LEFT_PARANTHESIS) {
        throw SyntaxErrorException("Missing ( token in If statement");
    }
}

Tokens::iterator IfStatementParser::checkConditionOfIfStatement(Tokens& tokens) const {
    auto end = find_if(tokens.begin(), tokens.end(), [](const shared_ptr<Token>& token) {
        return token->getType() == TokenType::LEFT_BRACE;
        });

    if (end == tokens.end()) {
        throw SyntaxErrorException("Missing { token in If statement");
    }

    // 'then' token 
    auto token = prev(end);
    // ')' token
    token = prev(token);
    if (token->get()->getType() != TokenType::RIGHT_PARANTHESIS) {
        throw SyntaxErrorException("Missing ) token in If statement");
    }

    return end;
}

void IfStatementParser::checkStartOfBlock(string value, Tokens& tokens) const {
    if (tokens[0]->getValue() != value) {
        throw SyntaxErrorException("Missing " + value + " name token in If statement's " + value + " block");
    }

    if (tokens[1]->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("Missing { token in If statement's " + value + " block");
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