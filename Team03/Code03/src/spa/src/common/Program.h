#pragma once

#include <vector>
#include "Procedure.h"

class Program {
public:
	Program();
	typedef vector<shared_ptr<Procedure>> ProcedureListContainer;
	void addToProcedureList(shared_ptr<Procedure> procedure);
	static shared_ptr<int> getAndIncrementStatementNumber();
	shared_ptr<ProcedureListContainer> getProcedureList();

private:
	shared_ptr<ProcedureListContainer> procedureList;
	static shared_ptr<int> statementNumber;
};