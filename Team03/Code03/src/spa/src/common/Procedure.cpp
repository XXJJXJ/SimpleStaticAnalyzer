#include "Procedure.h"

Procedure::Procedure(string procedureName) : procedureName(std::move(
    procedureName)), statementList({}) {}

void Procedure::addToStatementList(shared_ptr<Statement> statement) {
    (*statementList).push_back(statement);
}

shared_ptr<Procedure::StatementListContainer> Procedure::getStatementList() const {
    return statementList;
}

string Procedure::getName() const {
    return procedureName;
}

void Procedure::accept(shared_ptr<Visitor> visitor) {
    visitor->visitProcedure(make_shared<Procedure>(*this));
}