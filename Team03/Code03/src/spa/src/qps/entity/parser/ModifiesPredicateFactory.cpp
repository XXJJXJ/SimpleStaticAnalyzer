#include "ModifiesPredicateFactory.h"
#include "qps/entity/clause/ModifiesPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

ModifiesPredicateFactory::ModifiesPredicateFactory() {}
ModifiesPredicateFactory::~ModifiesPredicateFactory() {}

std::unique_ptr<Predicate> ModifiesPredicateFactory::createPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {
	std::vector<std::string> refs = extractRefs(tokens);

	if (refs.size() == 2) {
		std::variant<int, Synonym, std::string> lhs = stringToStatementRef(refs[0], synonymMap);
		std::variant<Synonym, std::string> rhs = stringToEntityRef(refs[1], synonymMap);
		std::unique_ptr<Predicate> predicate = std::make_unique<ModifiesPredicate>(lhs, rhs);
		return predicate;
	}
	else {
		throw SyntaxErrorException("Incorrect number of references in Modifies clause");
	}
}