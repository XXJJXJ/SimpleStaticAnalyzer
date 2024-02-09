#pragma once

#include "Statement.h"
#include "Variable.h"

class ReadStatement : public Statement {
public:
	ReadStatement(int statementNumber, Variable variable, string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	Variable getVariable() const;

private:
	const Variable& variable;
};