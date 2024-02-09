#pragma once

#include "StatementParser.h"
#include "common/Program.h"
#include "common/ReadStatement.h"

class ReadStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(vector<shared_ptr<Token>> tokens) override;
	string extractVariableName(vector<shared_ptr<Token>> tokens) const;
};