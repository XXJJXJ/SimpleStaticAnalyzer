#pragma once

#include "PredicateFactory.h"

class ModifiesPredicateFactory : public PredicateFactory {
public:
	ModifiesPredicateFactory();
	~ModifiesPredicateFactory();

	std::unique_ptr<Predicate> createPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap);
};