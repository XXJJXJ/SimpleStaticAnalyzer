#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "common/IfStatement.h"
#include "common/Program.h"

class IfStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(vector<shared_ptr<Token>>& tokens) override;
	shared_ptr<ConditionalOperation> extractCondition(vector<shared_ptr<Token>>& tokens);
	void checkStartOfIfStatement(vector<shared_ptr<Token>>& tokens) const;
	void checkStartOfElseStatement(vector<shared_ptr<Token>>& tokens) const;
	bool hasElseStatements(vector<shared_ptr<Token>>& tokens) const;
	bool isEndOfStatement(vector<shared_ptr<Token>>& tokens) const;
};