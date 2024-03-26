#include "WhileStatement.h"

WhileStatement::WhileStatement(
    int statementNumber,
    shared_ptr<ConditionalOperation> condition_,
    string procedureName) 
    : Statement(
        statementNumber,
        EntityType::While,
        std::move(procedureName)), condition(std::move(condition_)) {}

void WhileStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitWhileStatement(make_shared<WhileStatement>(*this));
}

void WhileStatement::addStatement(shared_ptr<Statement> statement) {
    statementList.push_back(statement);
}

shared_ptr<ConditionalOperation> WhileStatement::getCondition() const {
    return condition;
}

StatementList WhileStatement::getStatementList() const {
    return statementList;
}

EntityType WhileStatement::getType() const {
    return EntityType::While;
}

bool WhileStatement::isOfType(EntityType type) const {
    return type == EntityType::While || Statement::isOfType(type);
}