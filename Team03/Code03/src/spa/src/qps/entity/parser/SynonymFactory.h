#pragma once

#include "EntityFactory.h"
#include "common/EntityType.h"
#include "qps/entity/query/Synonym.h"


class SynonymFactory : public EntityFactory {
public:
	SynonymFactory();
	~SynonymFactory();

	std::shared_ptr<EntityObject> createEntityObject(const std::vector<std::string>& token);
	EntityType convertStringToEntityType(std::string curr);
};