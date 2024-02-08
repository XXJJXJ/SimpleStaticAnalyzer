#include "Statement.h"

Statement::Statement(
    int statement_number,
    string statement_type,
    string procedure_name)
    : statement_number(statement_number),
      statement_type(move(statement_type)),
      procedure_name(move(procedure_name)) {
}

int Statement::getStatementNumber() const {
    return statement_number;
}

string Statement::getStatementType() const {
    return statement_type;
}

string Statement::getProcedureName() const {
    return procedure_name;
}