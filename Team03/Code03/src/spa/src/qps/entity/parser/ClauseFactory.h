#pragma once

#include <string>
#include <memory>
#include <vector>
#include "qps/entity/clause/Clause.h"

class ClauseFactory {
public:
	virtual std::shared_ptr<Clause> createClauseObject(const std::vector<std::string>& token) = 0;
};