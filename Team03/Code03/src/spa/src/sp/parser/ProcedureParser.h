#pragma once

#include "common/Procedure.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "EntityParser.h"
#include "StatementParserFactory.h"

class ProcedureParser : public EntityParser<Procedure> {
public:
	shared_ptr<Procedure> parseEntity(vector<shared_ptr<Token>> tokens) override;
	static string extractProcedureName(vector<shared_ptr<Token>> tokens);
	static bool isEndOfProcedure(vector<shared_ptr<Token>> tokens);
};