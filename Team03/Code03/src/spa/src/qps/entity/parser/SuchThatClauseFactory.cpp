#include "SuchThatClauseFactory.h"
#include "PredicateFactoryManager.h"

SuchThatClauseFactory::SuchThatClauseFactory() {}
SuchThatClauseFactory::~SuchThatClauseFactory() {}

std::shared_ptr<Clause> SuchThatClauseFactory::createClauseObject(const std::vector<std::string>& tokens) {
	SuchThatClause suchThatClause;

	std::string firstWord = tokens[2];
	PredicateFactory* factory = PredicateFactoryManager::getPredicateFactory(firstWord);
	if (factory) {
		std::unique_ptr<Predicate> predicateObject = factory->createPredicate(tokens);
		suchThatClause.addPredicate(std::move(predicateObject));
	}

	std::shared_ptr<SuchThatClause> sharedSuchThat = std::make_shared<SuchThatClause>(suchThatClause);

	return sharedSuchThat;
}
