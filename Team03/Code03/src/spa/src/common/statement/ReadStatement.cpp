#include "ReadStatement.h"

ReadStatement::ReadStatement(
    int statementNumber, 
    shared_ptr<Variable> variable_, 
    string procedureName) 
    : variable(std::move(variable_)),
    Statement(
        std::move(statementNumber),
        EntityType::Read,
        std::move(procedureName)) {}

shared_ptr<Variable> ReadStatement::getVariable() const {
    return variable;
}

void ReadStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitReadStatement(make_shared<ReadStatement>(*this));
}

EntityType ReadStatement::getType() const {
    return EntityType::Read;
}

bool ReadStatement::isOfType(EntityType type) const {
    return type == EntityType::Read || Statement::isOfType(type);
}
