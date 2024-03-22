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
	bool getIsProcessedToken();
	bool getIsSubExpression();
	bool isEndOfTokens();
	void nextToken();
	void manageParentheses(TokenType tokenType, int index);
	void setArguments(bool isSubExpression, shared_ptr<int> index, shared_ptr<bool> isProcessedToken);
	void setIsSubExpression(bool isSubExpression);
	void updateNextToken();
	void checkTokens();

private:
	Tokens tokens;
	string tokenValue;
	shared_ptr<Token> token = nullptr;
	shared_ptr<bool> isProcessedTokenPointer = make_shared<bool>(isProcessedToken);
	shared_ptr<bool> isSubExpressionPointer = make_shared<bool>(isSubExpression);
	stack<TokenType> parentheses;
	unordered_map<int, TokenType> parenthesesIndexMap; 
	shared_ptr<int> indexPointer = make_shared<int>(index);
	int index = 0;
	bool isSetArguments = false;
	bool isProcessedToken = false;
	bool isSubExpression = false;
	bool hasMoreTokens();
	void incrementIndex();
	void markTokenAsProcessed();
	void setup(Tokens& tokens);
	void modifyParentheses(TokenType tokenType);
	void checkParentheses();
	virtual shared_ptr<Expression> parse() = 0;
};