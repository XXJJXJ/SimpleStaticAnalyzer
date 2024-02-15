#pragma once

#include "Util.h"
#include "Statement.h"
#include "ConditionalOperation.h"

class IfStatement : public Statement {
public:
    IfStatement(
        int statementNumber,
        shared_ptr<ConditionalOperation> condition,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    void addThenStatement(shared_ptr<Statement> statement);
    void addElseStatement(shared_ptr<Statement> statement);
    shared_ptr<ConditionalOperation> getCondition() const;
    Util::StatementListContainer getThenStatementList() const;
    Util::StatementListContainer getElseStatementList() const;

private:
    shared_ptr<ConditionalOperation> condition;
    Util::StatementListContainer thenStatementList;
    Util::StatementListContainer elseStatementList;
};