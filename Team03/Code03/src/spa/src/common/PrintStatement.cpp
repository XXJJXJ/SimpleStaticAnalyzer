#include "PrintStatement.h"

PrintStatement::PrintStatement(
    shared_ptr<int> statementNumber,
    shared_ptr<Variable> variable,
    shared_ptr<string> procedureName) : variable(variable),
    Statement(
        statementNumber,
        make_shared<string>("print"),
        procedureName) {}

shared_ptr<Variable> PrintStatement::getVariable() const {
    return variable;
}

void PrintStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitPrintStatement(make_shared<PrintStatement>(*this));
}