#include "PrintStatement.h"

PrintStatement::PrintStatement(
    int statementNumber,
    Variable variable,
    string procedureName) : variable(move(variable)),
    Statement(
        statementNumber,
        "print",
        procedureName) {}

Variable PrintStatement::getVariable() const {
    return variable;
}

void PrintStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitPrintStatement(make_shared<PrintStatement>(*this));
}