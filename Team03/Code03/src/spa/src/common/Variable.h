#pragma once

#include "Expression.h"

class Variable : public Expression {
public:
	Variable(string name);
	void accept(shared_ptr<Visitor> visitor) override;
	bool isLeafNodeExpression() override;
	std::size_t hash() const;
	bool operator==(const Variable& other) const;
};

namespace std {
    template <>
    struct hash<shared_ptr<Variable>> {
        std::size_t operator()(const shared_ptr<Variable>& obj) const {
            return obj->hash();
        }
    };

    template <>
    struct equal_to<shared_ptr<Variable>> {
        bool operator()(const shared_ptr<Variable>& lhs, const shared_ptr<Variable>& rhs) const {
            return *lhs == *rhs;
        }
    };
}