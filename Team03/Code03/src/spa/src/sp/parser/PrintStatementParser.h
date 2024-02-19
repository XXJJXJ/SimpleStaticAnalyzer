#pragma once
#include "StatementParser.h"
#include "common/Program.h"
#include "common/PrintStatement.h"

class PrintStatementParser : public StatementParser {
public:
	shared_ptr<Statement> parseEntity(Tokens& tokens) override;
	string extractVariableName(Tokens& tokens) const;
};