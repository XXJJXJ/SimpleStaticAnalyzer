#include "AssignStatement.h"

AssignStatement::AssignStatement(
    int statementNumber, 
    shared_ptr<Variable> variable_,
    string procedureName)
    : variable(variable_), expression(),
    Statement(statementNumber, EntityType::Assign, move(procedureName)) {}

void AssignStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitAssignStatement(make_shared<AssignStatement>(*this));
    expression->accept(visitor);
}

void AssignStatement::addExpression(shared_ptr<Expression> expr) {
    expression = expr;
}

shared_ptr<Variable> AssignStatement::getVariable() const {
    return variable;
}

shared_ptr<Expression> AssignStatement::getExpression() const {
    return expression;
}