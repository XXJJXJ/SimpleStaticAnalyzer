#pragma once

#include "common/Statement.h"
#include "common/Procedure.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "EntityParser.h"
#include "ExpressionParserFactory.h"

class StatementParser : public EntityParser<Statement> {
public:
	virtual shared_ptr<Statement> parseEntity(Tokens& tokens) = 0;
	string getProcedureName();
	void setProcedureName(string procedureName);

private:
	string procedureName;
};