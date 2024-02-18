#include "WhileStatementParser.h"

shared_ptr<Statement> WhileStatementParser::parseEntity(vector<shared_ptr<Token>>& tokens) {
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

shared_ptr<ConditionalOperation> WhileStatementParser::extractCondition(vector<shared_ptr<Token>>& tokens) {
    vector<shared_ptr<Token>> conditionTokens;
    // Erase 'while and (' from tokens
    tokens.erase(tokens.begin(), tokens.begin() + 2);
    
    auto end = find_if(tokens.begin(), tokens.end(), [](const std::shared_ptr<Token>& token) {
        return token->getValue() == "{";
        });

    if (end == tokens.end()) {
        throw SyntaxErrorException("While statement is missing a {");
    }

    auto token = prev(end);

    if (token->get()->getValue() != ")") {
        throw SyntaxErrorException("If statement condition should be bounded by ( and )");
    }

    for (auto i = tokens.begin(); i != end - 1; ++i) {
        conditionTokens.push_back(*i);
    }
    // Erasing all condition tokens and ) from tokens
    tokens.erase(tokens.begin(), end);

    auto expressionParser =
        ExpressionParserFactory::getExpressionParser(conditionTokens, "while");
    auto
        condition = (expressionParser->parseEntity(
            conditionTokens));

    if (!condition) {
        throw SyntaxErrorException("Invalid condition for while statement");
    }

    return dynamic_pointer_cast<ConditionalOperation>(condition);
}

void WhileStatementParser::checkStartOfWhileStatement(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getValue() != "while") {
        throw SyntaxErrorException("Missing while statement");
    }

    if (tokens[1]->getValue() != "(") {
        throw SyntaxErrorException("Missing ( at the start of while block");
    }
}

bool WhileStatementParser::isEndOfWhileStatement(vector<shared_ptr<Token>>& tokens) const {
    return tokens[0]->getValue() == "}";
}
