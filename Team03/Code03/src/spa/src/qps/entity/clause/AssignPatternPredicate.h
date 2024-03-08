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
    static bool isValidRhs(const std::string& rhs);
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
	AssignPatternPredicate(Synonym assignSyn, EntityRef lhs, std::string rhs);
	~AssignPatternPredicate() override = default;

};

#endif // ASSIGNPATTERNPREDICATE_H