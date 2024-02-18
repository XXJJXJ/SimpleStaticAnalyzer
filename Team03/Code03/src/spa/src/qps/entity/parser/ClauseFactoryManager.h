#include <string>
#include "ClauseFactory.h"

#ifndef SPA_CLAUSEFACTORYMANAGER_H
#define SPA_CLAUSEFACTORYMANAGER_H

class ClauseFactoryManager {
public:
	ClauseFactoryManager();
	~ClauseFactoryManager();

	static ClauseFactory* getClauseFactory(const std::string& firstWord);
};

#endif //SPA_CLAUSEFACTORYMANAGER_H