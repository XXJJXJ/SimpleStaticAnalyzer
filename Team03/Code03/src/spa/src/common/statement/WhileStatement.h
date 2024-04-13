#pragma once

#include "common/Util.h"
#include "Statement.h"
#include "common/expression/ConditionalOperation.h"

class WhileStatement : public Statement {
public:
    WhileStatement(int statementNumber, shared_ptr<ConditionalOperation> condition, string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    void addStatement(shared_ptr<Statement> statement);
    shared_ptr<ConditionalOperation> getCondition() const;
    StatementList getStatementList() const;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;

private:
    shared_ptr<ConditionalOperation> condition;
    StatementList statementList;
};

namespace std {
template<>
struct hash<shared_ptr<WhileStatement>> {
    std::size_t operator()(const shared_ptr<WhileStatement> &obj) const {
        return obj->hash();
    }
};

template<>
struct equal_to<shared_ptr<WhileStatement>> {
    bool operator()(const shared_ptr<WhileStatement> &lhs, const shared_ptr<WhileStatement> &rhs) const {
        return *lhs == *rhs;
    }
};
}