#pragma once

#include "StatementParser.h"
#include "common/Program.h"
#include "common/AssignStatement.h"

class AssignStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(vector<shared_ptr<Token>>& tokens) override;
	string extractVariableName(vector<shared_ptr<Token>>& tokens) const;
	vector<shared_ptr<Token>> extractExpression(vector<shared_ptr<Token>>& tokens) const;
	void checkEndOfStatement(vector<shared_ptr<Token>>& tokens) const;
};