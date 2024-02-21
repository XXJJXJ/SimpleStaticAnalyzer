#pragma once

#include "ClauseFactory.h"
#include "qps/entity/clause/PatternClause.h"

class PatternClauseFactory : public ClauseFactory {
public:
	PatternClauseFactory();
	~PatternClauseFactory();

	std::shared_ptr<Clause> createClauseObject(const std::vector<std::string>& token, const std::unordered_map<std::string, EntityType>& synonymMap);
};