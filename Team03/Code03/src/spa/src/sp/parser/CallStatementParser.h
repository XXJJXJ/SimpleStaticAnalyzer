#pragma once

#include "StatementParser.h"
#include "common/Program.h"
#include "common/statement/CallStatement.h"

class CallStatementParser : public StatementParser {
 public:
  shared_ptr<Statement> parseEntity(Tokens &tokens) override;
  string extractProcedureName(Tokens &tokens) const;
};