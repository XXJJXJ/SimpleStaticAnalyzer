#include "PredicateFactory.h"

class PredicateFactoryManager {
public:
	PredicateFactoryManager();
	~PredicateFactoryManager();

	static PredicateFactory* getPredicateFactory(const std::string& firstWord);
};