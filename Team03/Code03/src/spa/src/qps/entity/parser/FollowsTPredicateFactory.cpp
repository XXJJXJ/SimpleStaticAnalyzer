#include "FollowsTPredicateFactory.h"
#include "qps/entity/clause/FollowsTPredicate.h"

FollowsTPredicateFactory::FollowsTPredicateFactory() {}
FollowsTPredicateFactory::~FollowsTPredicateFactory() {}

std::unique_ptr<Predicate> FollowsTPredicateFactory::createPredicate(const std::vector<std::string>& tokens) {
	StatementRef lhs;
	StatementRef rhs;
	std::unique_ptr<Predicate> predicate = std::make_unique<FollowsTPredicate>(lhs, rhs);
	return predicate;
}