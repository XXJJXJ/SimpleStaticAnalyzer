#include "FollowsPredicateFactory.h"
#include "qps/entity/clause/FollowsPredicate.h"

FollowsPredicateFactory::FollowsPredicateFactory() {}
FollowsPredicateFactory::~FollowsPredicateFactory() {}

std::unique_ptr<Predicate> FollowsPredicateFactory::createPredicate(const std::vector<std::string>& tokens) {
	StatementRef lhs; 
	StatementRef rhs;
	std::unique_ptr<Predicate> predicate = std::make_unique<FollowsPredicate>(lhs, rhs);
	return predicate;
}