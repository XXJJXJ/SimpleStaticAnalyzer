#include "ParentPredicateFactory.h"
#include "qps/entity/clause/ParentPredicate.h"

ParentPredicateFactory::ParentPredicateFactory() {}
ParentPredicateFactory::~ParentPredicateFactory() {}

std::unique_ptr<Predicate> ParentPredicateFactory::createPredicate(const std::vector<std::string>& tokens) {
	StatementRef lhs;
	StatementRef rhs;
	std::unique_ptr<Predicate> predicate = std::make_unique<ParentPredicate>(lhs, rhs);
	return predicate;
}