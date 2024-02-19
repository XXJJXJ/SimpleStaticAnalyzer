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
    StatementListContainer getThenStatementList() const;
    StatementListContainer getElseStatementList() const;

private:
    shared_ptr<ConditionalOperation> condition;
    StatementListContainer thenStatementList;
    StatementListContainer elseStatementList;
};

namespace std {
    template <>
    struct hash<shared_ptr<IfStatement>> {
        std::size_t operator()(const shared_ptr<IfStatement>& obj) const {
            return obj->hash();
        }
    };

    template <>
    struct equal_to<shared_ptr<IfStatement>> {
        bool operator()(const shared_ptr<IfStatement>& lhs, const shared_ptr<IfStatement>& rhs) const {
            return *lhs == *rhs;
        }
    };
}