#pragma once

#include "PredicateFactory.h"

class ParentTPredicateFactory : public PredicateFactory {
public:
	ParentTPredicateFactory();
	~ParentTPredicateFactory();

	std::unique_ptr<Predicate> createPredicate(const std::vector<std::string>& tokens);
};