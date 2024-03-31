#pragma once

#include "Statement.h"
#include "common/expression/Variable.h"

class ReadStatement : public Statement {
public:
	ReadStatement(
		int statementNumber, 
		shared_ptr<Variable> variable, 
		string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	shared_ptr<Variable> getVariable() const;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;

private:
	const shared_ptr<Variable> variable;
};

namespace std {
    template <>
    struct hash<shared_ptr<ReadStatement>> {
        std::size_t operator()(const shared_ptr<ReadStatement>& obj) const {
            return obj->hash();
        }
    };

    template <>
    struct equal_to<shared_ptr<ReadStatement>> {
        bool operator()(const shared_ptr<ReadStatement>& lhs, const shared_ptr<ReadStatement>& rhs) const {
            return *lhs == *rhs;
        }
    };
}