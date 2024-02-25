#pragma once

#ifndef ASSIGNPATTERNPREDICATE_H
#define ASSIGNPATTERNPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"

// Forward declaration of Strategy to avoid circular dependency
class Strategy;

class AssignPatternPredicate : public Predicate {
private:
	Synonym assignSyn;
	EntityRef lhs;
	std::string rhs;
	bool isValidAssignSyn(const Synonym& assignSyn);
	bool isValidLhs(const EntityRef& lhs);
	bool isValidRhs(const std::string& rhs);
public:
	AssignPatternPredicate(Synonym assignSyn, EntityRef lhs, std::string rhs);
	~AssignPatternPredicate() override = default;

};

#endif // ASSIGNPATTERNPREDICATE_H