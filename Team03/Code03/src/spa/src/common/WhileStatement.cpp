#include "WhileStatement.h"

WhileStatement::WhileStatement(
    int statementNumber,
    shared_ptr<ConditionalOperation> condition_,
    string procedureName) : Statement(
        statementNumber,
        EntityType::While,
        move(procedureName)), condition(move(condition_)) {}

void WhileStatement::addStatement(shared_ptr<Statement> statement) {
    statementList.push_back(statement);
}

void WhileStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitWhileStatement(make_shared<WhileStatement>(*this));
}

shared_ptr<ConditionalOperation> WhileStatement::getCondition() const {
    return condition;
}

StatementListContainer WhileStatement::getStatementList() const {
    return statementList;
}

EntityType WhileStatement::getType() const {
    return EntityType::While;
}

bool WhileStatement::isOfType(EntityType type) const {
    return type == this->getType() || Statement::isOfType(type);
}