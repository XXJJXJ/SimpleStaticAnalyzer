#include "ReadStatement.h"

ReadStatement::ReadStatement(
    int statementNumber, 
    Variable variable, 
    string procedureName) : variable(move(variable)), 
    Statement(
        statementNumber,
        "read",
        procedureName) {}

Variable ReadStatement::getVariable() const {
    return variable;
}

void ReadStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitReadStatement(make_shared<ReadStatement>(*this));
}