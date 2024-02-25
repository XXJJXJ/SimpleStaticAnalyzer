#include "Statement.h"

Statement::Statement(
    int statementNumber_,
    EntityType statementType,
    string procedureName_)
    : statementNumber(statementNumber_),
      statementType(std::move(statementType)),
      procedureName(std::move(procedureName_)) {
}

int Statement::getStatementNumber() const {
    return statementNumber;
}

EntityType Statement::getStatementType() const {
    return statementType;
}

string Statement::getProcedureName() const {
    return procedureName;
}

string Statement::getName() const {
    return to_string(this->getStatementNumber());
}

std::size_t Statement::hash() const {
    std::hash<int> hasher;
    return hasher(getStatementNumber());
}

bool Statement::operator==(const Statement& other) const {
    return getStatementNumber() == other.getStatementNumber();
}

EntityType Statement::getType() const {
    return EntityType::Stmt;
}

bool Statement::isOfType(EntityType type) const {
    // Cannot use this->getType() it still returns the more specific type
    return type == EntityType::Stmt;
}

// Empty function to make Statement non-abstract
void Statement::accept(shared_ptr<Visitor> visitor) {

}
