#include "ConditionalOperationParser.h"

shared_ptr<Expression> ConditionalOperationParser::parse() {
    int index = *getIndexPointer();
    bool isSubExpression = getIsSubExpression();
    bool isProcessedToken = *getIsProcessedTokenPointer();

    try {
        shared_ptr<RelationalOperationParser> relationalOperationParser = make_shared<RelationalOperationParser>();
        relationalOperationParser->inheritArguments(getIndexPointer(), isSubExpression, getIsProcessedTokenPointer());
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
    
    this->inheritArguments(
        make_shared<int>(index),
        isSubExpression,
        make_shared < bool>(isProcessedToken));

    if (getTokenValue() == "!") {
        getNext();
        if (getTokenValue() == "(") {
            getNext();
            this->setIsSubExpression(true);
            auto conditionalExpression = parse();
            if (getTokenValue() != ")") {
                throw SyntaxErrorException("Missing ) in conditional expression");
            }

            getNext();
            pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
            arguments.first = conditionalExpression;
            return make_shared<ConditionalOperation>("!", arguments);
        }
    }
    else if (getTokenValue() == "(") {
        getNext();
        validateEnoughTokensToProcess();
        this->setIsSubExpression(true);
        auto leftConditionalExpression = parse();
        if (getTokenValue() != ")") {
            throw SyntaxErrorException("Missing ) in conditional expression");
        }

        getNext();
        string operation = getTokenValue();
        if (!(getTokenValue() == "&&" || getTokenValue() == "||")) {
            throw SyntaxErrorException("Missing && or ||");
        }
        getNext();

        if (getTokenValue() == "(") {
            getNext();
            this->setIsSubExpression(true);
            auto rightConditionalExpression = parse();
            if (*(getIndexPointer().get()) < getTokens()->size()) {
                getNext();
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