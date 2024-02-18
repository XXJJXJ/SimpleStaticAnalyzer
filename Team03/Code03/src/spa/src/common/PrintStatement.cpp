#include "PrintStatement.h"

PrintStatement::PrintStatement(
    int statementNumber,
    shared_ptr<Variable> variable,
    string procedureName) : variable(variable),
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
