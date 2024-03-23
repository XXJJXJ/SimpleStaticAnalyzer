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
	void manageParentheses(TokenType tokenType, int index);
	void setPairOfArguments(bool isSubExpression, shared_ptr<int> index, shared_ptr<bool> isProcessedToken);
	void setIsSubExpression(bool isSubExpression);
	void updateNextToken();
	void checkTokens();

private:
	Tokens tokens;
	string tokenValue;
	shared_ptr<Token> token = nullptr;
	shared_ptr<bool> isProcessedTokenPointer = make_shared<bool>(false);
	shared_ptr<bool> isSubExpressionPointer = make_shared<bool>(false);
	shared_ptr<bool> isSetArgumentPointer = make_shared<bool>(false);
	shared_ptr<int> indexPointer = make_shared<int>(0);
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