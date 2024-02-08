#pragma once

#include "Procedure.h"

Procedure::Procedure(string procedure_name) : procedure_name(move(
    procedure_name)), statement_list({}) {}

void Procedure::addToStatementList(shared_ptr<Statement> statement) {
    statement_list.push_back(statement);
}

Procedure::StatementListContainer Procedure::getStatementList() const {
    return statement_list;
}

string Procedure::getProcedureName() const {
    return procedure_name;
}

void Procedure::accept(shared_ptr<Visitor> visitor) {
    visitor->visitProcedure(make_shared<Procedure>(*this));
}