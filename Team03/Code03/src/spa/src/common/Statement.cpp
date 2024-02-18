#include "Statement.h"

Statement::Statement(
    int statementNumber,
    EntityType statementType,
    string procedureName)
    : statementNumber(statementNumber),
      statementType(move(statementType)),
      procedureName(move(procedureName)) {
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