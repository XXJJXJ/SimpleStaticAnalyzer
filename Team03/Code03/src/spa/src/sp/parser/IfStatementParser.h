#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "common/IfStatement.h"
#include "common/Program.h"

class IfStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(Tokens& tokens) override;
	shared_ptr<ConditionalOperation> extractCondition(Tokens& tokens);
	void checkStartOfIfStatement(Tokens& tokens) const;
	void checkStartOfElseStatement(Tokens& tokens) const;
	bool hasElseStatements(Tokens& tokens) const;
	bool isEndOfStatement(Tokens& tokens) const;
};