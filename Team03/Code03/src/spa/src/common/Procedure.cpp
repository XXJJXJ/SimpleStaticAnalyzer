#pragma once

#include "Procedure.h"

Procedure::Procedure(shared_ptr<string> procedure_name) : procedureName(move(
    procedureName)), statementList({}) {}

void Procedure::addToStatementList(shared_ptr<Statement> statement) {
    (*statementList).push_back(statement);
}

shared_ptr<Procedure::StatementListContainer> Procedure::getStatementList() const {
    return statementList;
}

shared_ptr<string> Procedure::getProcedureName() const {
    return procedureName;
}

void Procedure::accept(shared_ptr<Visitor> visitor) {
    visitor->visitProcedure(make_shared<Procedure>(*this));
}