#include "AssignStatement.h"

AssignStatement::AssignStatement(
    int statementNumber, 
    shared_ptr<Variable> variable_,
    string procedureName)
    : variable(variable_), expression(),
    Statement(statementNumber, EntityType::Assign, std::move(procedureName)) {}

void AssignStatement::accept(shared_ptr<Visitor> visitor) {
    expression->accept(visitor);
    visitor->visitAssignStatement(make_shared<AssignStatement>(*this));
}

void AssignStatement::addExpression(shared_ptr<Expression> expression_) {
    expression = expression_;
}

shared_ptr<Variable> AssignStatement::getVariable() const {
    return variable;
}

shared_ptr<Expression> AssignStatement::getExpression() const {
    return expression;
}

EntityType AssignStatement::getType() const {
    return EntityType::Assign;
}

bool AssignStatement::isOfType(EntityType type) const {
    return type == EntityType::Assign || Statement::isOfType(type);
}
