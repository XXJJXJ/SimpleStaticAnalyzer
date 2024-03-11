#include "PredicateFactory.h"
#include "qps/QueryValidator.h"
#include "qps/entity/clause/AssignPatternPredicate.h"
#include "qps/entity/clause/FollowsPredicate.h"
#include "qps/entity/clause/FollowsTPredicate.h"
#include "qps/entity/clause/ModifiesPredicate.h"
#include "qps/entity/clause/ParentPredicate.h"
#include "qps/entity/clause/ParentTPredicate.h"
#include "qps/entity/clause/UsesPredicate.h"
#include "common/spa_exception/SemanticErrorException.h"

std::shared_ptr<Predicate> PredicateFactory::createPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {	
	PredicateType predicateType = getPredicateType(tokens[0]);

    switch (predicateType) {
    case PredicateType::Follows: {
        FollowsPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<FollowsPredicate>(predicate);
    }
    case PredicateType::FollowsT: {
        FollowsTPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<FollowsTPredicate>(predicate);
    }
    case PredicateType::Modifies: {
        ModifiesPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToEntityRef(tokens[2], synonymMap));
        return std::make_shared<ModifiesPredicate>(predicate);
    }
    case PredicateType::Parent: {
        ParentPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<ParentPredicate>(predicate);
    }
    case PredicateType::ParentT: {
        ParentTPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToStatementRef(tokens[2], synonymMap));
        return std::make_shared<ParentTPredicate>(predicate);
    }
    case PredicateType::Uses: {
        UsesPredicate predicate(stringToStatementRef(tokens[1], synonymMap), stringToEntityRef(tokens[2], synonymMap));
        return std::make_shared<UsesPredicate>(predicate);
    }
    case PredicateType::Pattern: {
        AssignPatternPredicate predicate(Synonym(tokens[1], synonymMap), stringToEntityRef(tokens[2], synonymMap), tokens[3]);
        return std::make_shared<AssignPatternPredicate>(predicate);
    }
    }
}

std::variant<int, Synonym, std::string> PredicateFactory::stringToStatementRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	size_t len = token.size();
    if (len >= 2 && token[0] == '"' && token[len - 1] == '"') {
        return token.substr(1, len - 2);
	}
	else if (token == "_") {
		return token;
	}
	else if (QueryValidator::isInteger(token)) {
		return stoi(token);
	}
	else if (QueryValidator::isSynonym(token)) {
		return stringToSynonym(token, synonymMap);
	}
}

std::variant<Synonym, std::string> PredicateFactory::stringToEntityRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	size_t len = token.size();
	if (len >= 2 && token[0] == '"' && token[len - 1] == '"') {
		return token.substr(1, len - 2);
	}
	else if (token == "_") {
		return token;
	}
	else if (QueryValidator::isSynonym(token)) {
		return stringToSynonym(token, synonymMap);
	}
}

Synonym PredicateFactory::stringToSynonym(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	try {
		EntityType synonymType = synonymMap.at(token);
		Synonym synonym = Synonym(synonymType, token);
		return synonym;
	}
	catch (const std::out_of_range& e) {
		throw SemanticErrorException("Selected synonym '" + token + "' has not been declared");
	}
}