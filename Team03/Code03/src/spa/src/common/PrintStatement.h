#pragma once

#include "Statement.h"
#include "Variable.h"

class PrintStatement : public Statement {
public:
	PrintStatement(int statement_number, Variable variable, string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	Variable getVariable() const;

private:
	const Variable& variable;
};