#include "AssignStatement.h"

AssignStatement::AssignStatement(
    int statementNumber, 
    Variable variable,
    string procedureName)
    : variable(move(variable)), expression(),
    Statement(statementNumber, "assign", move(procedureName)) {}

void AssignStatement::accept(shared_ptr<Visitor> visitor) {
    visitor->visitAssignStatement(make_shared<AssignStatement>(*this));
    expression->accept(visitor);
}

void AssignStatement::addExpression(shared_ptr<Expression> expr) {
    expression = expr;
}

Variable AssignStatement::getVariable() const {
    return variable;
}

shared_ptr<Expression> AssignStatement::getExpression() const {
    return expression;
}