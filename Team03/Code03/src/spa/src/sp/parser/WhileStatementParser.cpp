#include "WhileStatementParser.h"

shared_ptr<Statement> WhileStatementParser::parseEntity(Tokens& tokens) {
    checkStartOfWhileStatement(tokens);  
    
    auto condition = extractCondition(tokens);
    auto whileStatement = make_shared<WhileStatement>(Program::getAndIncrementStatementNumber(),
        condition, getProcedureName());
    
    // Erase '{' from tokens
    tokens.erase(tokens.begin());
        
    while (!tokens.empty() && !isEndOfWhileStatement(tokens)) {
        auto statementParser = StatementParserFactory::getStatementParser(tokens);
        statementParser->setProcedureName(getProcedureName());
        auto loopStatement = statementParser->parseEntity(tokens);
        whileStatement->addStatement(loopStatement);
    }
    
    if (isEndOfWhileStatement(tokens)) {
        // Erase '}' from tokens
        tokens.erase(tokens.begin());
    }

    return whileStatement;
}

shared_ptr<ConditionalOperation> WhileStatementParser::extractCondition(Tokens& tokens) {
    Tokens conditionTokens;
    // Erase 'while and (' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);
    
    auto end = find_if(tokens.begin(), tokens.end(), [](const shared_ptr<Token>& token) {
        return token->getValue() == "{";
        });
    if (end == tokens.end()) {
        throw SyntaxErrorException("While statement is missing a {");
    }

    auto token = prev(end);
    if (token->get()->getValue() != ")") {
        throw SyntaxErrorException("While statement condition should be bounded by ( and )");
    }

    for (auto i = tokens.begin(); i != end - 1; ++i) {
        conditionTokens.push_back(*i);
    }

    // Erasing all condition tokens and ) from tokens
    tokens.erase(tokens.begin(), end);

    auto expressionParser =
        ExpressionParserFactory::getExpressionParser(conditionTokens, EntityType::While);
    auto
        condition = (expressionParser->parseEntity(
            conditionTokens));
    if (!condition) {
        throw SyntaxErrorException("Invalid condition for While statement");
    }

    return dynamic_pointer_cast<ConditionalOperation>(condition);
}

void WhileStatementParser::checkStartOfWhileStatement(Tokens& tokens) const {
    if (tokens[0]->getValue() != "while") {
        throw SyntaxErrorException("Missing While statement");
    }

    if (tokens[1]->getValue() != "(") {
        throw SyntaxErrorException("Missing ( at the start of While statement");
    }
}

bool WhileStatementParser::isEndOfWhileStatement(Tokens& tokens) const {
    return tokens[0]->getValue() == "}";
}