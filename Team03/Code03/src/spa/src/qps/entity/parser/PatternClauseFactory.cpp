#include "PatternClauseFactory.h"

PatternClauseFactory::PatternClauseFactory() {}
PatternClauseFactory::~PatternClauseFactory() {}

std::shared_ptr<EntityObject> PatternClauseFactory::createEntityObject(const std::vector<std::string>& token) {
	//TODO: implement
	PatternClause patternClause;
	std::shared_ptr<PatternClause> sharedPattern = std::make_shared<PatternClause>(patternClause);
	return sharedPattern;
}
