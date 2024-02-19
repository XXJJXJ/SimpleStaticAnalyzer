#include "UsesPredicateFactory.h"
#include "qps/entity/clause/UsesPredicate.h"

UsesPredicateFactory::UsesPredicateFactory() {}
UsesPredicateFactory::~UsesPredicateFactory() {}

std::unique_ptr<Predicate> UsesPredicateFactory::createPredicate(const std::vector<std::string>& tokens) {
	UsesLhsRef lhs = "x";
	EntityRef rhs = "x";
	std::unique_ptr<Predicate> predicate = std::make_unique<UsesPredicate>(lhs, rhs);
	return predicate;
}