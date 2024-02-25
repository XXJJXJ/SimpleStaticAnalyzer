#include "Procedure.h"

Procedure::Procedure(string procedureName_) : procedureName(
    procedureName_), statementList({}) {}

void Procedure::addToStatementList(shared_ptr<Statement> statement) {
    statementList.push_back(statement);
}

StatementListContainer Procedure::getStatementList() const {
    return statementList;
}

string Procedure::getName() const {
    return procedureName;
}

void Procedure::accept(shared_ptr<Visitor> visitor) {
    visitor->visitProcedure(make_shared<Procedure>(*this));
}

EntityType Procedure::getType() const {
    return EntityType::Procedure;
}

bool Procedure::isOfType(EntityType type) const {
    return type == EntityType::Procedure;
}
