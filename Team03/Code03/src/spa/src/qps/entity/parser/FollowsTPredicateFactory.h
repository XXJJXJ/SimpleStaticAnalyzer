#pragma once

#include "PredicateFactory.h"

class FollowsTPredicateFactory : public PredicateFactory {
public:
	FollowsTPredicateFactory();
	~FollowsTPredicateFactory();

	std::unique_ptr<Predicate> createPredicate(const std::vector<std::string>& tokens);
};