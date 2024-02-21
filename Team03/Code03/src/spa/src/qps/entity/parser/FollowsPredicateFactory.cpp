#include "FollowsPredicateFactory.h"
#include "qps/entity/clause/FollowsPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

FollowsPredicateFactory::FollowsPredicateFactory() {}
FollowsPredicateFactory::~FollowsPredicateFactory() {}

std::unique_ptr<Predicate> FollowsPredicateFactory::createPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {
	std::vector<std::string> refs = extractRefs(tokens);

	if (refs.size() == 2) {
		std::variant<int, Synonym, std::string> lhs = stringToStatementRef(refs[0], synonymMap);
		std::variant<int, Synonym, std::string> rhs = stringToStatementRef(refs[1], synonymMap);
		std::unique_ptr<Predicate> predicate = std::make_unique<FollowsPredicate>(lhs, rhs);
		return predicate;
	}
	else {
		throw SyntaxErrorException("Incorrect number of references in Follows clause");
	}
}