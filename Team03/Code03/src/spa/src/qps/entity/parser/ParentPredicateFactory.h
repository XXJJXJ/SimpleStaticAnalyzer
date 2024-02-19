#pragma once

#include "PredicateFactory.h"

class ParentPredicateFactory : public PredicateFactory {
public:
	ParentPredicateFactory();
	~ParentPredicateFactory();

	std::unique_ptr<Predicate> createPredicate(const std::vector<std::string>& tokens);
};