#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "common/IfStatement.h"
#include "common/Program.h"

class IfStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(Tokens& tokens) override;
	shared_ptr<ConditionalOperation> extractCondition(Tokens& tokens);
	void parseThenBlock(shared_ptr<IfStatement> ifStatement, Tokens& tokens);
	void parseElseBlock(shared_ptr<IfStatement> ifStatement, Tokens& tokens);
	void checkStartOfIfStatement(Tokens& tokens) const;
	Tokens::iterator checkConditionOfIfStatement(Tokens& tokens) const;
	void checkStartOfThenBlock(Tokens& tokens) const;
	void checkStartOfElseBlock (Tokens& tokens) const;
	bool isEndOfStatement(Tokens& tokens) const;
};