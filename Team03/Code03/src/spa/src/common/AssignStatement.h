#pragma once

#include "Statement.h"
#include "Expression.h"
#include "Variable.h"

class AssignStatement : public Statement {
public:
    AssignStatement(
        int statementNumber, 
        Variable variable,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    void addExpression(shared_ptr<Expression> expression);
    Variable getVariable() const;
    shared_ptr<Expression> getExpression() const;

private:
    Variable variable;
    shared_ptr<Expression> expression;
};