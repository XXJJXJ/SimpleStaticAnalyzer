#include "Statement.h"

Statement::Statement(
    int statementNumber_,
    string statementType_,
    string procedureName_)
    : statementNumber(statementNumber_),
      statementType(move(statementType_)),
      procedureName(move(procedureName_)) {
}

int Statement::getStatementNumber() const {
    return statementNumber;
}

string Statement::getStatementType() const {
    return statementType;
}

string Statement::getProcedureName() const {
    return procedureName;
}

string Statement::getName() const {
    return to_string(this->getStatementNumber());
}