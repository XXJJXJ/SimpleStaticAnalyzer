#include "EntityFactoryManager.h"
#include "SynonymFactory.h"
#include "SuchThatClauseFactory.h"
#include "PatternClauseFactory.h"
#include "common/spa_exception/SyntaxErrorException.h"

EntityFactoryManager::EntityFactoryManager() {}
EntityFactoryManager::~EntityFactoryManager() {}

EntityFactory* EntityFactoryManager::getEntityFactory(const std::string& firstWord) {
	if (firstWord == "stmt" || firstWord == "read" || firstWord == "print" || firstWord == "call" || firstWord == "while" || firstWord == "if" || firstWord == "assign" || firstWord == "variable" || firstWord == "constant" || firstWord == "procedure" || firstWord == "Select") {
		return new SynonymFactory();
	}
	else if (firstWord == "such") {
		return new SuchThatClauseFactory();
	}
	else if (firstWord == "pattern") {
		return new PatternClauseFactory();
	}
	else {
		throw new SyntaxErrorException("Invalid keyword");
	}
}