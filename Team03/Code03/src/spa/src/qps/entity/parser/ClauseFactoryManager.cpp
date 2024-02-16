#include "ClauseFactoryManager.h"
#include "SuchThatClauseFactory.h"
#include "PatternClauseFactory.h"
#include "common/spa_exception/SyntaxErrorException.h"

ClauseFactoryManager::ClauseFactoryManager() {}
ClauseFactoryManager::~ClauseFactoryManager() {}

ClauseFactory* ClauseFactoryManager::getClauseFactory(const std::string& firstWord) {
	if (firstWord == "such") {
		return new SuchThatClauseFactory();
	}
	else if (firstWord == "pattern") {
		return new PatternClauseFactory();
	}
	else {
		throw new SyntaxErrorException("Invalid keyword");
	}
}