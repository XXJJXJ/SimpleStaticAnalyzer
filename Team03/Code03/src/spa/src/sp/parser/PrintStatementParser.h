#pragma once
#include "StatementParser.h"
#include "common/Program.h"
#include "common/PrintStatement.h"

class PrintStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(vector<shared_ptr<Token>>& tokens) override;
	string extractVariableName(vector<shared_ptr<Token>>& tokens) const;
};