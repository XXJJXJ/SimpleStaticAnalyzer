#include "WhileStatement.h"

WhileStatement::WhileStatement(
    int statementNumber,
    shared_ptr<ConditionalOperation> condition,
    string procedureName) : Statement(
        statementNumber,
        "while",
        move(procedureName)), condition(move(condition)) {}

void WhileStatement::addStatement(shared_ptr<Statement> statement) {
    statementList.push_back(statement);
}

void WhileStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitWhileStatement(make_shared<WhileStatement>(*this));
}

shared_ptr<ConditionalOperation> WhileStatement::getCondition() const {
    return condition;
}

WhileStatement::StatementListContainer WhileStatement::getStatementList() const {
    return statementList;
}

