#pragma once

#include "Statement.h"
#include "ConditionalOperation.h"

class IfStatement : public Statement {
public:
    typedef vector<shared_ptr<Statement>> StatementListContainer;
    IfStatement(
        int statementNumber,
        shared_ptr<ConditionalOperation> condition,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    void addThenStatement(shared_ptr<Statement> statement);
    void addElseStatement(shared_ptr<Statement> statement);
    shared_ptr<ConditionalOperation> getCondition() const;
    StatementListContainer getThenStatementList() const;
    StatementListContainer getElseStatementList() const;

private:
    shared_ptr<ConditionalOperation> condition;
    StatementListContainer thenStatementList;
    StatementListContainer elseStatementList;
};