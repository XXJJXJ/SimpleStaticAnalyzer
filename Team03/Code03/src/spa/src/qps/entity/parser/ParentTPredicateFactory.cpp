#include "ParentTPredicateFactory.h"
#include "qps/entity/clause/ParentTPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

ParentTPredicateFactory::ParentTPredicateFactory() {}
ParentTPredicateFactory::~ParentTPredicateFactory() {}

std::unique_ptr<Predicate> ParentTPredicateFactory::createPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {
	std::vector<std::string> refs = extractRefs(tokens);

	if (refs.size() == 2) {
		std::variant<int, Synonym, std::string> lhs = stringToStatementRef(refs[0], synonymMap);
		std::variant<int, Synonym, std::string> rhs = stringToStatementRef(refs[1], synonymMap);
		std::unique_ptr<Predicate> predicate = std::make_unique<ParentTPredicate>(lhs, rhs);
		return predicate;
	}
	else {
		throw SyntaxErrorException("Incorrect number of references in Parent* clause");
	}
}