#pragma once

#include "PredicateFactory.h"

class FollowsPredicateFactory : public PredicateFactory {
public:
	FollowsPredicateFactory();
	~FollowsPredicateFactory();

	std::unique_ptr<Predicate> createPredicate(const std::vector<std::string>& tokens);
};