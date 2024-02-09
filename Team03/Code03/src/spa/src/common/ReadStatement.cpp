#include "ReadStatement.h"

ReadStatement::ReadStatement(
    int statementNumber, 
    shared_ptr<Variable> variable, 
    string procedureName) : variable(variable), 
    Statement(
        statementNumber,
       "read",
        procedureName) {}

shared_ptr<Variable> ReadStatement::getVariable() const {
    return variable;
}

void ReadStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitReadStatement(make_shared<ReadStatement>(*this));
}