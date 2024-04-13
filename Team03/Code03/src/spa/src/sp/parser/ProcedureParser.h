#pragma once

#include "common/Procedure.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "EntityParser.h"
#include "StatementParserFactory.h"

class ProcedureParser : public EntityParser<Procedure> {
public:
	shared_ptr<Procedure> parseEntity(Tokens& tokens) override;
	static string extractProcedureName(Tokens& tokens);
	static bool isEndOfProcedure(Tokens& tokens);
};