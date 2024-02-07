#pragma once

#include "Statement.h"
#include "Variable.h"

class PrintStatement : public Statement {
public:
	PrintStatement(int statement_number, Variable var, string procedure_name);
	void accept(shared_ptr<Visitor> visitor) override;
	Variable getVariable() const;

private:
	const Variable& variable;
};