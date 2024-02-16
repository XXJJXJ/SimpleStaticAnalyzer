#include "ConditionalOperationParser.h"

shared_ptr<Expression> ConditionalOperationParser::parse() {
    int index = getIndex();
    bool isSubExpression = getIsSubExpression();
    bool isProcessedToken = getIsProcessedToken();

    try {
        shared_ptr<RelationalOperationParser> relationalOperationParser = make_shared<RelationalOperationParser>();
        relationalOperationParser->inheritArguments(index, isSubExpression, isProcessedToken);
        auto relationalExpression = relationalOperationParser->parseEntity(*getTokens());
        this->setIsSubExpression(false);
        if (relationalExpression) {
            pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
            arguments.first = relationalExpression;
            updateToken();
            return make_shared<ConditionalOperation>("relationalExpression", arguments);
        }
    }
    catch (SpaException& e) {
        string errorMessage = "Error parsing relational expression";
    }

    this->inheritArguments(index,
        isSubExpression,
        isProcessedToken);

    if (getTokenType() == TokenType::NOT) {
        getNext();
        if (getTokenType() == TokenType::LEFT_PARENTHESIS) {
            getNext();
            this->setIsSubExpression(true);
            auto conditionalExpression = parse();
            if (getTokenType() != TokenType::RIGHT_PARENTHESIS) {
                throw SyntaxErrorException("Missing ) in conditional expression");
            }

            getNext();
            pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
            arguments.first = conditionalExpression;
            return make_shared<ConditionalOperation>("!", arguments);
        }
    }
    else if (getTokenType() == TokenType::LEFT_PARENTHESIS) {
        getNext();
        validateEnoughTokensToProcess();
        this->setIsSubExpression(true);
        auto leftConditionalExpression = parse();
        if (getTokenType() != TokenType::RIGHT_PARENTHESIS) {
            throw SyntaxErrorException("Missing ) in conditional expression");
        }

        getNext();
        string operation = getTokenValue();
        if (!(getTokenType() == TokenType::AND || getTokenType() == TokenType::OR)) {
            throw SyntaxErrorException("Missing && or ||");
        }
        getNext();

        if (getTokenType() == TokenType::LEFT_PARENTHESIS) {
            getNext();
            this->setIsSubExpression(true);
            auto rightConditionalExpression = parse();
            if (index < getTokens()->size()) {
                getNext();
            }
            if (getTokenType() != TokenType::RIGHT_PARENTHESIS) {
                throw SyntaxErrorException("Missing ) in conditional expression");
            }
            pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
            arguments.first = leftConditionalExpression;
            arguments.second = rightConditionalExpression;
            return make_shared<ConditionalOperation>(operation, arguments);
        }
        else {
            throw SyntaxErrorException("Missing ( in conditional expression");
        }
    }

    throw SyntaxErrorException("Invalid Conditional Operation");
}