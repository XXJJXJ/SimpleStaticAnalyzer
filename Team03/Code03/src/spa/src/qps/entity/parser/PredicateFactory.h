#pragma once

#include <memory>
#include "qps/entity/clause/Predicate.h"

class PredicateFactory {
public:
	virtual std::unique_ptr<Predicate> createPredicate(const std::vector<std::string>& tokens) = 0;
};