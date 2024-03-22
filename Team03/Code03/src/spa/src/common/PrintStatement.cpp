#include "PrintStatement.h"

PrintStatement::PrintStatement(
    int statementNumber,
    shared_ptr<Variable> variable_,
    string procedureName) 
    : variable(std::move(variable_)),
    Statement(
        std::move(statementNumber),
        EntityType::Print,
        std::move(procedureName)) {}

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
    return type == EntityType::Print || Statement::isOfType(type);
}
