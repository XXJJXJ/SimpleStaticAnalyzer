#pragma once

#include "Program.h"

int Program::statementNumber = 1;

Program::Program() : procedureList({}) { statementNumber = 1; }

void Program::addToProcedureList(shared_ptr<Procedure> procedure) {
	procedureList->push_back(procedure);
}

shared_ptr<Program::ProcedureListContainer> Program::getProcedureList() {
	return procedureList;
}

int Program::getAndIncrementStatementNumber() {
	return statementNumber++;
}