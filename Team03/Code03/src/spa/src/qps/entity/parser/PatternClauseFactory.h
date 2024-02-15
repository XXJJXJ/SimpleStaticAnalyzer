#pragma once

#include "EntityFactory.h"
#include "qps/entity/clause/PatternClause.h"

class PatternClauseFactory : public EntityFactory {
public:
	PatternClauseFactory();
	~PatternClauseFactory();

	std::shared_ptr<EntityObject> createEntityObject(const std::vector<std::string>& token);
};