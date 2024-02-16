#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "common/Program.h"
#include "common/WhileStatement.h"

class WhileStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(vector<shared_ptr<Token>>& tokens) override;
	shared_ptr<ConditionalOperation> extractCondition(vector<shared_ptr<Token>>& tokens);
	void checkStartOfWhileStatement(vector<shared_ptr<Token>>& tokens) const;
	void checkStartOfLoopStatement(vector<shared_ptr<Token>>& tokens) const;
	bool isEndOfWhileStatement(vector<shared_ptr<Token>>& tokens) const;
};