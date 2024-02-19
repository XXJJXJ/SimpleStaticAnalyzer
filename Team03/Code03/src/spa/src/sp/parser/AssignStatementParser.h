#pragma once

#include "StatementParser.h"
#include "common/Program.h"
#include "common/AssignStatement.h"

class AssignStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(Tokens& tokens) override;
	string extractVariableName(Tokens& tokens) const;
	Tokens extractExpression(Tokens& tokens) const;
	void checkEndOfStatement(Tokens& tokens) const;
};