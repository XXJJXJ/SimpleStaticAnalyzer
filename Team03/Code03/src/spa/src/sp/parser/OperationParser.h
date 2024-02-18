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
	shared_ptr<int> getIndexPointer();
	void getNext();
	shared_ptr<Tokens> getTokens();
	void updateToken();
	bool getIsProcessedToken();
	shared_ptr<bool> getIsProcessedTokenPointer();
	bool getIsSubExpression();
	void setIsSubExpression(bool isSubExpression);
	void inheritArguments(shared_ptr<int> index, bool isSubExpression, shared_ptr<bool> isProcessedToken);
	void validateEnoughTokensToProcess();
	void addParenthesis(TokenType type, string val, int index);

private:
	vector<shared_ptr<Token>> tokens;
	virtual shared_ptr<Expression> parse() = 0;
	shared_ptr<Token> token = nullptr;
	string tokenValue;
	int index = 0;
	shared_ptr<int> indexPointer = make_shared<int>(index);
	bool isProcessedToken = false;
	shared_ptr<bool> isProcessedTokenPointer = make_shared<bool>(isProcessedToken);
	bool isSubExpression = false;
	shared_ptr<bool> isSubExpressionPointer = make_shared<bool>(isSubExpression);
	void setup(vector<shared_ptr<Token>>& tokens);
	bool isInheritArguments = false;
	void validateForBalancedParenthesis();
	stack<string> parenthesesContainer;
	unordered_map<int, string> parenthesesIndexMappings;
};