#pragma once

#include "Util.h"
#include "Statement.h"
#include "ConditionalOperation.h"

class WhileStatement : public Statement {
public:
    WhileStatement(
        int statementNumber,
        shared_ptr<ConditionalOperation> condition,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    void addStatement(shared_ptr<Statement> statement);
    shared_ptr<ConditionalOperation> getCondition() const;
    Util::StatementListContainer getStatementList() const;

private:
    shared_ptr<ConditionalOperation> condition;
    Util::StatementListContainer statementList;
};