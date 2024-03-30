#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "common/Program.h"
#include "common/statement/WhileStatement.h"

class WhileStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(Tokens& tokens) override;
	shared_ptr<ConditionalOperation> extractCondition(Tokens& tokens);
	void checkStartOfWhileStatement(Tokens& tokens) const;
	bool isEndOfWhileStatement(Tokens& tokens) const;
};