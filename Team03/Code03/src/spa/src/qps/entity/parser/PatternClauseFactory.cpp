#include "PatternClauseFactory.h"

PatternClauseFactory::PatternClauseFactory() {}
PatternClauseFactory::~PatternClauseFactory() {}

std::shared_ptr<Clause> PatternClauseFactory::createClauseObject(const std::vector<std::string>& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	//TODO: implement
	PatternClause patternClause;
	std::shared_ptr<PatternClause> sharedPattern = std::make_shared<PatternClause>(patternClause);
	return sharedPattern;
}
