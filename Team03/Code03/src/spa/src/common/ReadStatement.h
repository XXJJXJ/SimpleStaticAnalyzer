#pragma once

#include "Statement.h"
#include "Variable.h"

class ReadStatement : public Statement {
public:
	ReadStatement(int statement_number, Variable variable, string procedure_name);
	void accept(shared_ptr<Visitor> visitor) override;
	Variable getVariable() const;

private:
	const Variable& variable;
};