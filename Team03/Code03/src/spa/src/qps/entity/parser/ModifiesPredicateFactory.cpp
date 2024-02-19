#include "ModifiesPredicateFactory.h"
#include "qps/entity/clause/ModifiesPredicate.h"

ModifiesPredicateFactory::ModifiesPredicateFactory() {}
ModifiesPredicateFactory::~ModifiesPredicateFactory() {}

std::unique_ptr<Predicate> ModifiesPredicateFactory::createPredicate(const std::vector<std::string>& tokens) {
	ModifiesLhsRef lhs = "x";
    EntityRef rhs = "x";
	std::unique_ptr<Predicate> predicate = std::make_unique<ModifiesPredicate>(lhs, rhs);
	return predicate;
}