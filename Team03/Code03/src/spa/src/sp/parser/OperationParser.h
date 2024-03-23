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
	shared_ptr<bool> getIsProcessedTokenPointer();
	shared_ptr<Tokens> getTokens();
	shared_ptr<Expression> parseEntity(Tokens& tokens) override;
	int getIndex();
	bool getIsSubExpression();
	bool isEndOfTokens();
	void nextToken();
	void setNextToken();
	void manageParentheses(TokenType tokenType, int index);
	void setIsSubExpression(bool isSubExpression);
	void setPairOfArguments(bool isSubExpression, shared_ptr<int> index, shared_ptr<bool> isProcessedToken);

private:
	Tokens tokens;
	string tokenValue;
	shared_ptr<Token> token = nullptr;
	shared_ptr<int> indexPointer = make_shared<int>(0);
	shared_ptr<bool> isProcessedTokenPointer = make_shared<bool>(false);
	shared_ptr<bool> isSubExpressionPointer = make_shared<bool>(false);
	shared_ptr<bool> isSetPairOfArgumentsPointer = make_shared<bool>(false);
	stack<TokenType> parentheses;
	unordered_map<int, TokenType> indexParenthesesMap; 
	bool hasMoreTokens();
	void incrementIndex();
	void markTokenAsProcessed();
	void setup(Tokens& tokens);
	void modifyParentheses(TokenType tokenType);
	void checkParentheses();
	virtual shared_ptr<Expression> parse() = 0;
};