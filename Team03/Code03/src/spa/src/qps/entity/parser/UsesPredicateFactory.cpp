#include "UsesPredicateFactory.h"
#include "qps/entity/clause/UsesPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

UsesPredicateFactory::UsesPredicateFactory() {}
UsesPredicateFactory::~UsesPredicateFactory() {}

std::unique_ptr<Predicate> UsesPredicateFactory::createPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {
	std::vector<std::string> refs = extractRefs(tokens);

	if (refs.size() == 2) {
		std::variant<int, Synonym, std::string> lhs = stringToStatementRef(refs[0], synonymMap);
		std::variant<Synonym, std::string> rhs = stringToEntityRef(refs[1], synonymMap);
		std::unique_ptr<Predicate> predicate = std::make_unique<UsesPredicate>(lhs, rhs);
		return predicate;
	}
	else {
		throw SyntaxErrorException("Incorrect number of references in Parent* clause");
	}
}