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
	TokenType getTokenType();
	string getTokenValue();
	shared_ptr<int> getIndexPointer();
	shared_ptr<bool> getIsProcessedTokenPointer();
	shared_ptr<Tokens> getTokens();
	int getIndex();
	bool getIsProcessedToken();
	bool getIsSubExpression();
	void getNextToken();
	bool isEndOfStatement();
	void addParenthesis(string value, int index);
	void setArguments(shared_ptr<int> index, bool isSubExpression, shared_ptr<bool> isProcessedToken);
	void setIsSubExpression(bool isSubExpression);
	void updateNextToken();
	void validateTokensToProcess();

private:
	vector<shared_ptr<Token>> tokens;
	shared_ptr<Token> token = nullptr;
	string tokenValue;
	shared_ptr<bool> isProcessedTokenPointer = make_shared<bool>(isProcessedToken);
	shared_ptr<bool> isSubExpressionPointer = make_shared<bool>(isSubExpression);
	stack<string> parenthesesContainer;
	unordered_map<int, string> parenthesesIndexMappings; int index = 0;
	shared_ptr<int> indexPointer = make_shared<int>(index);
	bool isSetArguments = false;
	bool isProcessedToken = false;
	bool isSubExpression = false;
	void setup(vector<shared_ptr<Token>>& tokens);
	void validateBalancedParenthesis();
	virtual shared_ptr<Expression> parse() = 0;
};