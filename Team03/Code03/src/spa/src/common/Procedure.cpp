#pragma once

#include "Procedure.h"

Procedure::Procedure(string procedure_name) : procedureName(move(
    procedureName)), statementList({}) {}

void Procedure::addToStatementList(shared_ptr<Statement> statement) {
    statementList.push_back(statement);
}

Procedure::StatementListContainer Procedure::getStatementList() const {
    return statementList;
}

string Procedure::getProcedureName() const {
    return procedureName;
}

void Procedure::accept(shared_ptr<Visitor> visitor) {
    visitor->visitProcedure(make_shared<Procedure>(*this));
}