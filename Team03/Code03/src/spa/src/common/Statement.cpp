#include "Statement.h"

Statement::Statement(
    shared_ptr<int> statementNumber,
    shared_ptr<string> statementType,
    shared_ptr<string> procedureName)
    : statementNumber(statementNumber),
      statementType(move(statementType)),
      procedureName(move(procedureName)) {
}

shared_ptr<int> Statement::getStatementNumber() const {
    return statementNumber;
}

shared_ptr<string> Statement::getStatementType() const {
    return statementType;
}

shared_ptr<string> Statement::getProcedureName() const {
    return procedureName;
}