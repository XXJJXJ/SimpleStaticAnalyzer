#include "PrintStatement.h"

PrintStatement::PrintStatement(
    int statementNumber,
    shared_ptr<Variable> variable_,
    string procedureName) : variable(variable_),
    Statement(
        statementNumber,
        EntityType::Print,
        procedureName) {}

shared_ptr<Variable> PrintStatement::getVariable() const {
    return variable;
}

void PrintStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitPrintStatement(make_shared<PrintStatement>(*this));
}

EntityType PrintStatement::getType() const {
    return EntityType::Print;
}

bool PrintStatement::isOfType(EntityType type) const {
    return type == this->getType() || Statement::isOfType(type);
}
