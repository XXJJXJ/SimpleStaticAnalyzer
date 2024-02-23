#include "PredicateFactory.h"
#include "qps/QueryValidator.h"
#include "qps/entity/clause/FollowsPredicate.h"
#include "qps/entity/clause/FollowsTPredicate.h"
#include "qps/entity/clause/ModifiesPredicate.h"
#include "qps/entity/clause/ParentPredicate.h"
#include "qps/entity/clause/ParentTPredicate.h"
#include "qps/entity/clause/UsesPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/SemanticErrorException.h"

enum class PredicateType {
	Follows,
	FollowsT,
	Modifies,
	Parent,
	ParentT,
	Uses,
	Pattern,
	Invalid
};

PredicateType getPredicateType(const std::string& keyword) {
	static const std::unordered_map<std::string, PredicateType> keywordMap = {
		{"Follows", PredicateType::Follows},
		{"Follows*", PredicateType::FollowsT},
		{"Modifies", PredicateType::Modifies},
		{"Parent", PredicateType::Parent},
		{"Parent*", PredicateType::ParentT},
		{"Uses", PredicateType::Uses},
		{"pattern", PredicateType::Pattern}
	};

	auto it = keywordMap.find(keyword);
	return (it != keywordMap.end()) ? it->second : PredicateType::Invalid;
}

std::shared_ptr<Predicate> PredicateFactory::createPredicate(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {	
	if (tokens.size() > 2 && tokens[0] == "such" && tokens[1] == "that") {
		std::vector<std::string> predicateTokens(tokens.begin() + 2, tokens.end());
	}

	std::vector<std::string> refs = extractRefs(tokens);
	PredicateType predicateType = getPredicateType(tokens[0]);

	if (refs.size() == 2) {
		switch (predicateType) {
		case PredicateType::Follows: {
			FollowsPredicate predicate(stringToStatementRef(refs[0], synonymMap), stringToStatementRef(refs[1], synonymMap));
			return std::make_shared<FollowsPredicate>(predicate);
		}
		case PredicateType::FollowsT: {
			FollowsTPredicate predicate(stringToStatementRef(refs[0], synonymMap), stringToStatementRef(refs[1], synonymMap));
			return std::make_shared<FollowsTPredicate>(predicate);
		}
		case PredicateType::Modifies: {
			ModifiesPredicate predicate(stringToStatementRef(refs[0], synonymMap), stringToEntityRef(refs[1], synonymMap));
			return std::make_shared<ModifiesPredicate>(predicate);
		}
		case PredicateType::Parent: {
			ParentPredicate predicate(stringToStatementRef(refs[0], synonymMap), stringToStatementRef(refs[1], synonymMap));
			return std::make_shared<ParentPredicate>(predicate);
		}
		case PredicateType::ParentT: {
			ParentTPredicate predicate(stringToStatementRef(refs[0], synonymMap), stringToStatementRef(refs[1], synonymMap));
			return std::make_shared<ParentTPredicate>(predicate);
		}
		case PredicateType::Uses: {
			UsesPredicate predicate(stringToStatementRef(refs[0], synonymMap), stringToEntityRef(refs[1], synonymMap));
			return std::make_shared<UsesPredicate>(predicate);
		}
		default:
			throw new SyntaxErrorException("Invalid relationship keyword");
		}
	}
	else {
		throw new SyntaxErrorException("Invalid number of arguments in such that clause");
	}
}

std::vector<std::string> PredicateFactory::extractRefs(const std::vector<std::string>& tokens) {
	std::vector<std::string> results;

	size_t len = tokens.size();
	bool isRef = true;

	if (len > 3 && tokens[1] == "(" && tokens[len - 1] == ")") {
		for (size_t i = 2; i < len - 1; i++) {
			std::string token = tokens[i];
			size_t tokenLen = token.size();
			if (isRef) {
				results.push_back(token);
				isRef = false;
			}
			else if (token == "," && i < len-2) {
				isRef = true;
			}
			else {
				throw SyntaxErrorException("Invalid syntax in clause");
			}
		}
	}
	else {
		throw SyntaxErrorException("Invalid syntax in clause");
	}

	return results;
}

std::variant<int, Synonym, std::string> PredicateFactory::stringToStatementRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	QueryValidator qv;
	size_t len = token.size();
	if (len >= 2 && token[0] == '"' && token[len - 1] == '"') {
		return token.substr(1, len - 1);
	}
	else if (token == "_") {
		return token;
	}
	else if (qv.isInteger(token)) {
		return stoi(token);
	}
	else if (qv.isSynonym(token)) {
		return stringToSynonym(token, synonymMap);
	}
	else {
		throw SyntaxErrorException("Invalid syntax in clause");
	}
}

std::variant<Synonym, std::string> PredicateFactory::stringToEntityRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	QueryValidator qv;
	size_t len = token.size();
	if (len >= 2 && token[0] == '"' && token[len - 1] == '"') {
		return token.substr(1, len - 1);
	}
	else if (token == "_") {
		return token;
	}
	else if (qv.isSynonym(token)) {
		return stringToSynonym(token, synonymMap);
	}
	else {
		throw SyntaxErrorException("Invalid syntax in clause");
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