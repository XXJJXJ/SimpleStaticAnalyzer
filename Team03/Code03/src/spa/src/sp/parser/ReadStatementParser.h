#pragma once

#include "StatementParser.h"
#include "common/Program.h"
#include "common/ReadStatement.h"

class ReadStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(Tokens& tokens) override;
	string extractVariableName(Tokens& tokens) const;
};