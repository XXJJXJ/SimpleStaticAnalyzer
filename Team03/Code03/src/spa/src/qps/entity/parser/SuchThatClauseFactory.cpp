#include "SuchThatClauseFactory.h"
#include "PredicateFactoryManager.h"
#include "common/spa_exception/SyntaxErrorException.h"

SuchThatClauseFactory::SuchThatClauseFactory() {}
SuchThatClauseFactory::~SuchThatClauseFactory() {}

std::shared_ptr<Clause> SuchThatClauseFactory::createClauseObject(const std::vector<std::string>& tokens) {
	SuchThatClause suchThatClause;

	if (tokens[1] == "that" && tokens.size() > 2) {
		std::string firstWord = tokens[2];
		std::vector<std::string> predicateTokens(tokens.begin() + 2, tokens.end());

		PredicateFactory* factory = PredicateFactoryManager::getPredicateFactory(firstWord);
		if (factory) {
			std::unique_ptr<Predicate> predicateObject = factory->createPredicate(tokens);
			suchThatClause.addPredicate(std::move(predicateObject));
		}

		std::shared_ptr<SuchThatClause> sharedSuchThat = std::make_shared<SuchThatClause>(suchThatClause);

		return sharedSuchThat;
	}
	else {
		throw SyntaxErrorException("Invalid such that clause syntax");
	}
	
}
