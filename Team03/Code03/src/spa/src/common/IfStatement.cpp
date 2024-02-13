#include "IfStatement.h"

IfStatement::IfStatement(
    int statementNumber,
    shared_ptr<ConditionalOperation> condition,
    string procedureName) : Statement(
        statement_number,
        "if",
        move(procedureName)), condition(move(condition)) {}

void IfStatement::addThenStatement(shared_ptr<Statement> statement) {
    thenStatementList.push_back(statement);
}

void IfStatement::addElseStatement(shared_ptr<Statement> statement) {
    elseStatementList.push_back(statement);
}

void IfStatement::accept(shared_ptr<visitor> visitor) {
    visitor->VisitIfStatement(make_shared<IfStatement>(*this));
}

shared_ptr<ConditionalOperation> IfStatement::getCondition() const {
    return condition;
}

IfStatement::StatementListContainer IfStatement::getThenStatementList() const {
    return thenStatementList;
}

IfStatement::StatementListContainer IfStatement::getElseStatementList() const {
    return elseStatementList;
}
