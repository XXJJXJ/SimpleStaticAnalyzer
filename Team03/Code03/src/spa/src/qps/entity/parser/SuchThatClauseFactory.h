#pragma once

#include "ClauseFactory.h"
#include "qps/entity/clause/SuchThatClause.h"

class SuchThatClauseFactory : public ClauseFactory {
public:
	SuchThatClauseFactory();
	~SuchThatClauseFactory();

	std::shared_ptr<Clause> createClauseObject(const std::vector<std::string>& token, const std::unordered_map<std::string, EntityType>& synonymMap);
};