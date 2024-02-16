#include "WhileStatementParser.h"

shared_ptr<Statement> WhileStatementParser::parseEntity(vector<shared_ptr<Token>>& tokens) {
    checkStartOfWhileStatement(tokens);  

    auto condition = extractCondition(tokens);
    auto whileStatement = make_shared<WhileStatement>(Program::getAndIncrementStatementNumber(),
        condition, getProcedureName());
    
    checkStartOfLoopStatement(tokens);
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
        return token->getType() == TokenType::LEFT_BRACE;
        });

    if (end == tokens.end()) {
        throw SyntaxErrorException("Condition of a while statement should be bounded by ( and )");
    }

    for (auto i = tokens.begin(); i != end - 1; ++i) {
        conditionTokens.push_back(*i);
        // Erase condition from tokens
        tokens.erase(i);
    }

    // Erase ')' from tokens
    tokens.erase(tokens.begin());

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

    if (tokens[1]->getType() != TokenType::LEFT_PARENTHESIS) {
        throw SyntaxErrorException("Missing ( at the start of while block");
    }
}

void WhileStatementParser::checkStartOfLoopStatement(vector<shared_ptr<Token>>& tokens) const {
    if (tokens[0]->getType() != TokenType::LEFT_BRACE) {
        throw SyntaxErrorException("Missing { at the start of while loop block");
    }
}

bool WhileStatementParser::isEndOfWhileStatement(vector<shared_ptr<Token>>& tokens) const {
    return find_if(tokens.begin(), tokens.end(),
        [&](shared_ptr<Token> const ptr) {
            return ptr->getType() == TokenType::RIGHT_BRACE;
        }) != tokens.end();
}
