#include "IfStatement.h"

IfStatement::IfStatement(
    int statementNumber,
    shared_ptr<ConditionalOperation> condition,
    string procedureName) 
    : Statement(
        std::move(statementNumber),
        EntityType::If,
        std::move(procedureName)), condition(std::move(condition)) {}

void IfStatement::addThenStatement(shared_ptr<Statement> statement) {
    thenStatementList.push_back(statement);
}

void IfStatement::addElseStatement(shared_ptr<Statement> statement) {
    elseStatementList.push_back(statement);
}

void IfStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitIfStatement(make_shared<IfStatement>(*this));
}

shared_ptr<ConditionalOperation> IfStatement::getCondition() const {
    return condition;
}

StatementList IfStatement::getThenStatementList() const {
    return thenStatementList;
}

StatementList IfStatement::getElseStatementList() const {
    return elseStatementList;
}

EntityType IfStatement::getType() const {
    return EntityType::If;
}

bool IfStatement::isOfType(EntityType type) const {
    return type == EntityType::If || Statement::isOfType(type);
}
