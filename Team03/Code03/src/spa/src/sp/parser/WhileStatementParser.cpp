#include "WhileStatementParser.h"

shared_ptr<Statement> WhileStatementParser::parseEntity(Tokens& tokens) {
    checkStartOfWhileStatement(tokens);

    shared_ptr<ConditionalOperation> condition = extractCondition(tokens);
    shared_ptr<WhileStatement> whileStatement = make_shared<WhileStatement>(Program::getAndIncrementStatementNumber(),
        condition, getProcedureName());

    // Erase '{' from tokens
    tokens.erase(tokens.begin());

    while (!tokens.empty() && !isEndOfWhileStatement(tokens)) {
        shared_ptr<StatementParser> statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(getProcedureName());
        shared_ptr<Statement> loopStatement = statementParser->parseEntity(tokens);
        whileStatement->addStatement(loopStatement);
    }

    if (whileStatement->getStatementList().size() == 0) {
        throw SyntaxErrorException("Empty While statement");
    }

    if (isEndOfWhileStatement(tokens)) {
        // Erase '}' from tokens
        tokens.erase(tokens.begin());
    }
    else {
        throw SyntaxErrorException("Missing } token in While statement");
    }

    return whileStatement;
}

shared_ptr<ConditionalOperation> WhileStatementParser::extractCondition(Tokens& tokens) {
    Tokens conditionTokens;
    // Erase 'while and (' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    auto end = find_if(tokens.begin(), tokens.end(), [](const shared_ptr<Token>& token) {
        return token->getType() == TokenType::LEFT_BRACE;
        });
    if (end == tokens.end()) {
        throw SyntaxErrorException("Missing { token in While statement");
    }

    auto token = prev(end);
    if (token->get()->getType() != TokenType::RIGHT_PARANTHESIS) {
        throw SyntaxErrorException("Missing ) token in While statement");
    }

    for (auto i = tokens.begin(); i != end - 1; ++i) {
        conditionTokens.push_back(*i);
    }

    // Erasing all condition tokens and ) from tokens
    tokens.erase(tokens.begin(), end);

    shared_ptr<ExpressionParser> expressionParser =
        ExpressionParserFactory::getExpressionParser(conditionTokens, EntityType::While);
    shared_ptr<Expression> condition = 
        (expressionParser->parseEntity(conditionTokens));
    if (!condition) {
        throw SyntaxErrorException("Invalid condition for While statement");
    }

    return dynamic_pointer_cast<ConditionalOperation>(condition);
}

void WhileStatementParser::checkStartOfWhileStatement(Tokens& tokens) const {
    if (tokens[0]->getValue() != "while") {
        throw SyntaxErrorException("Missing while name token");
    }

    if (tokens[1]->getType() != TokenType::LEFT_PARANTHESIS) {
        throw SyntaxErrorException("Missing ( token in While statement");
    }
}

bool WhileStatementParser::isEndOfWhileStatement(Tokens& tokens) const {
    if (tokens.size() > 0) {
        return tokens[0]->getType() == TokenType::RIGHT_BRACE;
    }
    else {
        return false;
    }
}