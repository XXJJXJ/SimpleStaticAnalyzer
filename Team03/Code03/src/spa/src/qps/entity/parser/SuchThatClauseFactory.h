#pragma once

#include "EntityFactory.h"
#include "qps/entity/clause/SuchThatClause.h"

class SuchThatClauseFactory : public EntityFactory {
public:
	SuchThatClauseFactory();
	~SuchThatClauseFactory();

	std::shared_ptr<EntityObject> createEntityObject(const std::vector<std::string>& token);
};