#include "SuchThatClauseFactory.h"

SuchThatClauseFactory::SuchThatClauseFactory() {}
SuchThatClauseFactory::~SuchThatClauseFactory() {}

std::shared_ptr<Clause> SuchThatClauseFactory::createClauseObject(const std::vector<std::string>& token) {
	//TODO: implement
	SuchThatClause suchThatClause;
	std::shared_ptr<SuchThatClause> sharedSuchThat = std::make_shared<SuchThatClause>(suchThatClause);

	return sharedSuchThat;
}
