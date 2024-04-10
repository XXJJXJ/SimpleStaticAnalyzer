#pragma once

#ifndef ASSIGNPATTERNPREDICATE_H
#define ASSIGNPATTERNPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"
#include "qps/entity/evaluation/HeaderTable.h"

// Forward declaration of Strategy to avoid circular dependency
class Strategy;

class AssignPatternPredicate : public Predicate {
private:
	Synonym assignSyn;
	EntityRef lhs;
	std::string rhs;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
	AssignPatternPredicate(Synonym assignSyn, EntityRef lhs, std::string rhs);
	~AssignPatternPredicate() override = default;
    [[nodiscard]] PredicateType getType() const override;
	bool operator==(const AssignPatternPredicate &other) const;
	std::size_t hash() const override;
	bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<AssignPatternPredicate>> {
        std::size_t operator()(const shared_ptr<AssignPatternPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<AssignPatternPredicate>> {
        bool operator()(const shared_ptr<AssignPatternPredicate>& lhs, const shared_ptr<AssignPatternPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif // ASSIGNPATTERNPREDICATE_H