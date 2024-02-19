#include "ParentTPredicateFactory.h"
#include "qps/entity/clause/ParentTPredicate.h"

ParentTPredicateFactory::ParentTPredicateFactory() {}
ParentTPredicateFactory::~ParentTPredicateFactory() {}

std::unique_ptr<Predicate> ParentTPredicateFactory::createPredicate(const std::vector<std::string>& tokens) {
	StatementRef lhs;
	StatementRef rhs;
	std::unique_ptr<Predicate> predicate = std::make_unique<ParentTPredicate>(lhs, rhs);
	return predicate;
}