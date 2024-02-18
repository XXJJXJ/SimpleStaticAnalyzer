#include "ConditionalOperationParser.h"

shared_ptr<Expression> ConditionalOperationParser::parse() {
    int index = *getIndexPointer();
    bool isSubExpression = getIsSubExpression();
    bool isProcessedToken = *getIsProcessedTokenPointer();

    try {
        shared_ptr<RelationalOperationParser> relationalOperationParser = make_shared<RelationalOperationParser>();
        relationalOperationParser->setArguments(getIndexPointer(), isSubExpression, getIsProcessedTokenPointer());
        auto relationalExpression = relationalOperationParser->parseEntity(*getTokens());
        this->setIsSubExpression(false);
        if (relationalExpression) {
            pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
            arguments.first = relationalExpression;
            updateNextToken();
            return make_shared<ConditionalOperation>("relationalExpression", arguments);
        }
    }
    catch (SpaException& e) {
        string errorMessage = "Error parsing relational expression";
    }
    
    this->setArguments(
        make_shared<int>(index),
        isSubExpression,
        make_shared < bool>(isProcessedToken));

    if (getTokenValue() == "!") {
        getNextToken();
        if (getTokenValue() == "(") {
            getNextToken();
            this->setIsSubExpression(true);
            auto conditionalExpression = parse();
            if (getTokenValue() != ")") {
                throw SyntaxErrorException("Missing ) in conditional expression");
            }

            getNextToken();
            pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
            arguments.first = conditionalExpression;
            return make_shared<ConditionalOperation>("!", arguments);
        }
    }
    else if (getTokenValue() == "(") {
        getNextToken();
        validateTokens();
        this->setIsSubExpression(true);
        auto leftConditionalExpression = parse();
        if (getTokenValue() != ")") {
            throw SyntaxErrorException("Missing ) in conditional expression");
        }

        getNextToken();
        string operation = getTokenValue();
        if (!(getTokenValue() == "&&" || getTokenValue() == "||")) {
            throw SyntaxErrorException("Missing && or || in conditional expression");
        }
        getNextToken();

        if (getTokenValue() == "(") {
            getNextToken();
            this->setIsSubExpression(true);
            auto rightConditionalExpression = parse();
            if (*(getIndexPointer().get()) < getTokens()->size()) {
                getNextToken();
            }
            if (getTokenValue() != ")") {
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