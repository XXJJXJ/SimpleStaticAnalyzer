#pragma once

#include <vector>
#include "Procedure.h"

class Program {
public:
	typedef vector<shared_ptr<Procedure>> ProcedureListContainer;
	void addToProcedureList(shared_ptr<Procedure> procedure);
	static int getNextStatementNumber();
	ProcedureListContainer getProcedureList();

private:
	ProcedureListContainer procedure_list;
	static int statement_number;
};