#pragma once

#include "Expression.h"

class Constant : public Expression {
public:
	explicit Constant(string value);
	void accept(shared_ptr<Visitor> visitor) override;
	bool isLeafNode() override;
    std::size_t hash() const;
	bool operator==(const Constant& other) const;
    [[nodiscard]] EntityType getType() const override;
    [[nodiscard]] bool isOfType(EntityType type) const override;
    [[nodiscard]] int getValue() const;
};

namespace std {
    template <>
    struct hash<shared_ptr<Constant>> {
        std::size_t operator()(const shared_ptr<Constant>& obj) const {
            return obj->hash();
        }
    };

    template <>
    struct equal_to<shared_ptr<Constant>> {
        bool operator()(const shared_ptr<Constant>& lhs, const shared_ptr<Constant>& rhs) const {
            return *lhs == *rhs;
        }
    };
}
