#pragma once

#include "Statement.h"
#include "Variable.h"

class ReadStatement : public Statement {
public:
	ReadStatement(
		int statementNumber, 
		shared_ptr<Variable> variable, 
		string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	shared_ptr<Variable> getVariable() const;

private:
	const shared_ptr<Variable> variable;
};