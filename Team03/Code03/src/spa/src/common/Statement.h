#pragma once

#include <string>
#include <vector>
#include "Entity.h"
#include "EntityType.h"

class Statement : public Entity {
public:
    Statement(
        int statementNumber,
        EntityType statementType,
        string procedureName);
    void accept(shared_ptr<Visitor> visitor) override;
    int getStatementNumber() const;
    EntityType getStatementType() const;
    string getProcedureName() const;
    string getName() const override;
    [[nodiscard]] EntityType getType() const override;

    std::size_t hash() const;
	bool operator==(const Statement& other) const;
    [[nodiscard]] bool isOfType(EntityType type) const override;

private:
    const int statementNumber;
    EntityType statementType;
    string procedureName;
};

namespace std {
    template <>
    struct hash<shared_ptr<Statement>> {
        std::size_t operator()(const shared_ptr<Statement>& obj) const {
            return obj->hash();
        }
    };

    template <>
    struct equal_to<shared_ptr<Statement>> {
        bool operator()(const shared_ptr<Statement>& lhs, const shared_ptr<Statement>& rhs) const {
            return *lhs == *rhs;
        }
    };
}