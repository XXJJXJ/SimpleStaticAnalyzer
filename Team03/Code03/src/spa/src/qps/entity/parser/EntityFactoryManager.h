#include <string>
#include "EntityFactory.h"

#ifndef SPA_ENTITYFACTORYMANAGER_H
#define SPA_ENTITYFACTORYMANAGER_H

class EntityFactoryManager {
public:
	EntityFactoryManager();
	~EntityFactoryManager();

	static EntityFactory* getEntityFactory(const std::string& firstWord);
};

#endif //SPA_ENTITYFACTORYMANAGER_H