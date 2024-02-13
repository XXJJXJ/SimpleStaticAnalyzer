#pragma once

#include "Statement.h"
#include "ConditionalOperation.h"

class WhileStatement : public Statement {
public:
    typedef vector<shared_ptr<Statement>> StatementListContainer;
    WhileStatement(
        int statementNumber,
        shared_ptr<ConditionalOperation> condition,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    void addStatement(shared_ptr<Statement> statement);
    shared_ptr<ConditionalOperation> getCondition() const;
    StatementListContainer getStatementList() const;

private:
    shared_ptr<ConditionalOperation> condition;
    StatementListContainer statementList;
};