#include "ReadStatement.h"

ReadStatement::ReadStatement(int statement_number, Variable variable, string procedure_name) 
    : variable(move(variable)), 
    Statement(
            statement_number,
            "read",
            procedure_name) {}

Variable ReadStatement::getVariable() const {
    return variable;
}

void ReadStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitReadStatement(make_shared<ReadStatement>(*this));
}