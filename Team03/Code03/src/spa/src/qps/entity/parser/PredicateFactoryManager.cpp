#include "PredicateFactoryManager.h"
#include "FollowsPredicateFactory.h"
#include "FollowsTPredicateFactory.h"
#include "ModifiesPredicateFactory.h"
#include "ParentPredicateFactory.h"
#include "ParentTPredicateFactory.h"
#include "UsesPredicateFactory.h"
#include "common/spa_exception/SyntaxErrorException.h"

PredicateFactoryManager::PredicateFactoryManager() {}
PredicateFactoryManager::~PredicateFactoryManager() {}

PredicateFactory* PredicateFactoryManager::getPredicateFactory(const std::string& firstWord) {
	if (firstWord == "Follows") {
		return new FollowsPredicateFactory();
	}
	else if (firstWord == "Follows*") {
		return new FollowsTPredicateFactory();
	}
	else if (firstWord == "Modifies") {
		return new ModifiesPredicateFactory();
	}
	else if (firstWord == "Parent") {
		return new ParentPredicateFactory();
	}
	else if (firstWord == "Parent*") {
		return new ParentTPredicateFactory();
	}
	else if (firstWord == "Uses") {
		return new UsesPredicateFactory();
	}
	else {
		throw new SyntaxErrorException("Invalid relationship keyword");
	}
}