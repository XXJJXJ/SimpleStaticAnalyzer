#pragma once

#include "common/Util.h"
#include "Statement.h"
#include "common/expression/ConditionalOperation.h"

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
    StatementList getThenStatementList() const;
    StatementList getElseStatementList() const;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;

private:
    shared_ptr<ConditionalOperation> condition;
    StatementList thenStatementList;
    StatementList elseStatementList;
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