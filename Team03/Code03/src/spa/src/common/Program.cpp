#pragma once

#include "Program.h"

int Program::statement_number = 1;

Program::Program() : procedure_list({}) { statement_number = 1; }

void Program::addToProcedureList(shared_ptr<Procedure> procedure) {
	procedure_list.push_back(procedure);
}

Program::ProcedureListContainer Program::getProcedureList() {
	return procedure_list;
}

int Program::getNextStatementNumber() {
	return statement_number++;
}