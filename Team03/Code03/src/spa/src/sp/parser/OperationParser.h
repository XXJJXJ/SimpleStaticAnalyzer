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
	shared_ptr<Expression> parseEntity(Tokens& tokens) override;
	TokenType getTokenType();
	string getTokenValue();
	shared_ptr<int> getIndexPointer();
	shared_ptr<bool> getIsProcessedTokenPointer();
	shared_ptr<Tokens> getTokens();
	int getIndex();
	bool getIsProcessedToken();
	bool getIsSubExpression();
	void getNextToken();
	bool isEndOfTokens();
	void addParenthesis(TokenType tokenType, int index);
	void setArguments(shared_ptr<int> index, bool isSubExpression, shared_ptr<bool> isProcessedToken);
	void setIsSubExpression(bool isSubExpression);
	void updateNextToken();
	void validateTokens();

private:
	Tokens tokens;
	shared_ptr<Token> token = nullptr;
	string tokenValue;
	shared_ptr<bool> isProcessedTokenPointer = make_shared<bool>(isProcessedToken);
	shared_ptr<bool> isSubExpressionPointer = make_shared<bool>(isSubExpression);
	stack<TokenType> parenthesesStorage;
	unordered_map<int, TokenType> parenthesesToIndexMap; 
	shared_ptr<int> indexPointer = make_shared<int>(index);
	int index = 0;
	bool isSetArguments = false;
	bool isProcessedToken = false;
	bool isSubExpression = false;
	void setup(Tokens& tokens);
	void validateParenthesis();
	virtual shared_ptr<Expression> parse() = 0;
};