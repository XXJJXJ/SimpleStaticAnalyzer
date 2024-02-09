#pragma once

#include "Program.h"

shared_ptr<int> Program::statementNumber = make_shared<int>(1);

Program::Program() : procedureList({}) { shared_ptr<int>statementNumber = make_shared<int>(1); }

void Program::addToProcedureList(shared_ptr<Procedure> procedure) {
	procedureList->push_back(procedure);
}

shared_ptr<Program::ProcedureListContainer> Program::getProcedureList() {
	return procedureList;
}

shared_ptr<int> Program::getAndIncrementStatementNumber() {
	int tempValue = *statementNumber; 
	++(*statementNumber);
	return make_shared<int>(tempValue);
}