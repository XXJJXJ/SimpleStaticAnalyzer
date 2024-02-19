#pragma once

#include "PredicateFactory.h"

class UsesPredicateFactory : public PredicateFactory {
public:
	UsesPredicateFactory();
	~UsesPredicateFactory();

	std::unique_ptr<Predicate> createPredicate(const std::vector<std::string>& tokens);
};