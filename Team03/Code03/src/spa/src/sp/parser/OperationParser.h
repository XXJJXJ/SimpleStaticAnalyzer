#pragma once

#include <stack>
#include <unordered_map>
#include "ExpressionParser.h"
#include "common/Operation.h"
#include "../tokenizer/ArithmeticToken.h"
#include "../tokenizer/RelationalToken.h"
#include "../tokenizer/ConditionalToken.h"

class OperationParser : public ExpressionParser {
public:
	string getTokenValue();
	TokenType getTokenType();
	shared_ptr<int> getIndexPointer();
	shared_ptr<bool> getIsSubExpressionPointer();
	shared_ptr<bool> getIsProcessedTokenPointer();
	shared_ptr<Tokens> getTokens();
	shared_ptr<Expression> parseEntity(Tokens& tokens) override;
	bool isEndOfTokens();
	void nextToken();
	void setNextToken();
	void manageParentheses(TokenType tokenType);
	void setIsSubExpression(bool isSubExpression);
	void setPairOfArguments(shared_ptr<bool> isSubExpression, shared_ptr<int> index, shared_ptr<bool> isProcessedToken);

private:
	Tokens tokens;
	shared_ptr<Token> token = nullptr;
	shared_ptr<int> indexPointer = make_shared<int>(0);
	shared_ptr<bool> isProcessedTokenPointer = make_shared<bool>(false);
	shared_ptr<bool> isSubExpressionPointer = make_shared<bool>(false);
	shared_ptr<bool> isSetPairOfArgumentsPointer = make_shared<bool>(false);
	stack<TokenType> parentheses;
	bool hasMoreTokens();
	void incrementIndex();
	void markTokenAsProcessed();
	void setTokens(bool isInitialise, Tokens& tokens);
	void checkParentheses();
	virtual shared_ptr<Expression> parse() = 0;
};