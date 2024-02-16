#pragma once

#include "ClauseFactory.h"
#include "qps/entity/clause/SuchThatClause.h"

class SuchThatClauseFactory : public ClauseFactory {
public:
	SuchThatClauseFactory();
	~SuchThatClauseFactory();

	std::shared_ptr<ClauseObject> createClauseObject(const std::vector<std::string>& token);
};