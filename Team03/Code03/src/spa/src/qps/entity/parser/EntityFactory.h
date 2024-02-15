#pragma once

#include <string>
#include <memory>
#include <vector>
#include "EntityObject.h"

class EntityFactory {
public:
	virtual std::shared_ptr<EntityObject> createEntityObject(const std::vector<std::string>& token) = 0;
};