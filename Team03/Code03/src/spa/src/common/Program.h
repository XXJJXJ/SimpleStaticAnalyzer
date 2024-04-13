#pragma once

#include <vector>
#include "Procedure.h"

class Program {
public:
	Program();
	typedef vector<shared_ptr<Procedure>> ProcedureListContainer;
	void addToProcedureList(shared_ptr<Procedure> procedure);
	static int getAndIncrementStatementNumber();
	ProcedureListContainer getProcedureList();

private:
	ProcedureListContainer procedureList;
	static int statementNumber;
};