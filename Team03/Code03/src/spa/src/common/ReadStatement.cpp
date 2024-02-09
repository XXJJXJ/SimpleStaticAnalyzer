#include "ReadStatement.h"

ReadStatement::ReadStatement(
    shared_ptr<int> statementNumber, 
    shared_ptr<Variable> variable, 
    shared_ptr<string> procedureName) : variable(variable), 
    Statement(
        statementNumber,
        make_shared<string>("read"),
        procedureName) {}

shared_ptr<Variable> ReadStatement::getVariable() const {
    return variable;
}

void ReadStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitReadStatement(make_shared<ReadStatement>(*this));
}