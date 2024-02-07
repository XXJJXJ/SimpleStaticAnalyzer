#include "PrintStatement.h"

PrintStatement::PrintStatement(int statement_number,
    Variable var,
    string procedure_name) : variable(move(var)),
    Statement(
        statement_number,
        "print",
        procedure_name) {}

Variable PrintStatement::getVariable() const {
    return variable;
}

void PrintStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitPrintStatement(make_shared<PrintStatement>(*this));
}