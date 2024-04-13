#pragma once

#include "Statement.h"
#include "common/expression/Expression.h"
#include "common/expression/Variable.h"

class AssignStatement : public Statement {
public:
    AssignStatement(
        int statementNumber, 
        shared_ptr<Variable> variable,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    void addExpression(shared_ptr<Expression> expression);
    shared_ptr<Variable> getVariable() const;
    shared_ptr<Expression> getExpression() const;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;

private:
    shared_ptr<Variable> variable;
    shared_ptr<Expression> expression;
};

namespace std {
    template <>
    struct hash<shared_ptr<AssignStatement>> {
        std::size_t operator()(const shared_ptr<AssignStatement>& obj) const {
            return obj->hash();
        }
    };

    template <>
    struct equal_to<shared_ptr<AssignStatement>> {
        bool operator()(const shared_ptr<AssignStatement>& lhs, const shared_ptr<AssignStatement>& rhs) const {
            return *lhs == *rhs;
        }
    };
}