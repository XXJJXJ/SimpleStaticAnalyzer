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
	shared_ptr<Expression> parseEntity(vector<shared_ptr<Token>>& tokens) override;
	bool isEndOfStatement();
	TokenType getTokenType();
	string getTokenValue();
	int getIndex();
	void getNext();
	shared_ptr<Tokens> getTokens();
	bool getIsProcessedToken();
	bool getIsSubExpression();
	void setIsSubExpression(bool isSubExpression);
	void updateToken();
	void inheritArguments(int index, bool isSubExpression, bool isProcessedToken);
	void validateEnoughTokensToProcess();
	void addParenthesis(TokenType type, string val, int index);

private:
	vector<shared_ptr<Token>> tokens;
	virtual shared_ptr<Expression> parse() = 0;
	shared_ptr<Token> token = nullptr;
	string tokenValue;
	int index = 0;
	bool isProcessedToken = false;
	bool isSubExpression = false;
	void setup(vector<shared_ptr<Token>>& tokens);
	bool isInheritArguments = false;
	void validateForBalancedParenthesis();
	stack<string> parenthesesContainer;
	unordered_map<int, string> parenthesesIndexMappings;
};