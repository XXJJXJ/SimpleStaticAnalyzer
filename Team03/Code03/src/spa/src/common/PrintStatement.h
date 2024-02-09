#pragma once

#include "Statement.h"
#include "Variable.h"

class PrintStatement : public Statement {
public:
	PrintStatement(
		int statement_number, 
		shared_ptr<Variable> variable, 
		string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	shared_ptr<Variable> getVariable() const;

private:
	const shared_ptr<Variable> variable;
};