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
    bool isValidRow(const std::vector<std::shared_ptr<Entity>>& row) const;
    static bool isValidRhs(const std::string& rhs);
public:
	AssignPatternPredicate(Synonym assignSyn, EntityRef lhs, std::string rhs);
	~AssignPatternPredicate() override = default;
    [[nodiscard]] shared_ptr<BaseTable> getTable(QueryManager& qm) override;

};

#endif // ASSIGNPATTERNPREDICATE_H