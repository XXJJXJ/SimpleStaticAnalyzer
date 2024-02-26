#include "PredicateFactory.h"
#include "qps/QueryValidator.h"
#include "qps/entity/clause/AssignPatternPredicate.h"
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
	PredicateType predicateType = getPredicateType(tokens[0]);
    std::vector<std::string> refs;

    if (predicateType == PredicateType::Pattern) {
        std::vector<std::string> patternTokens(tokens.begin() + 1, tokens.end());
        refs = extractPatternRefs(patternTokens);
    } else {
        refs = extractRefs(tokens);
    }

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
        case PredicateType::Pattern: {
            Synonym assignSyn = Synonym(tokens[1], synonymMap);
            AssignPatternPredicate predicate(assignSyn, stringToEntityRef(refs[0], synonymMap), refs[1]);
            return std::make_shared<AssignPatternPredicate>(predicate);
        }
		default:
			throw new SyntaxErrorException("Invalid relationship keyword");
		}
	}
	else {
		throw SyntaxErrorException("Invalid number of arguments in such that clause");
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

std::vector<std::string> PredicateFactory::extractPatternRefs(const std::vector<std::string>& tokens) {
	std::vector<std::string> results;

	size_t len = tokens.size();
	bool isRef = true;
	// a **** ( **** _ **** , **** _ **** " **** +temp" **** _ **** ) ****
	bool isSecond = false;
	bool isPattern = false;
	if (len > 3 && tokens[1] == "(" && tokens[len - 1] == ")") {
		for (size_t i = 2; i < len - 1; i++) {
			std::string token = tokens[i];
			size_t tokenLen = token.size();
			if (isRef) {
				if (isSecond) {
					if (token == "_") {
						string res = token;
						i++;
						while (i < len - 1) {
							res.append(tokens[i]);
							if (tokens[i] == "_") {
								break;
							}
							i++;
						}
						if (res.back() != '_') {
							throw SyntaxErrorException("ExtractPatternRefs: pattern no matching _ : " + res + " " + res.back());
						}
						results.push_back(res);
					} else {
						results.push_back(token);
					}
				} else {
					results.push_back(token);
				}
				isRef = false;
			}
			else if (token == "," && i < len-2) {
				isSecond = true;
				isRef = true;
			}
			else {
				throw SyntaxErrorException("ExtractPatternRefs: Invalid syntax in clause");
			}
		}
	}
	else {
		throw SyntaxErrorException("ExtractPatternRefs: Invalid syntax in clause");
	}
	return results;
}

std::variant<int, Synonym, std::string> PredicateFactory::stringToStatementRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
	QueryValidator qv;
	size_t len = token.size();
    if (len >= 2 && token[0] == '"' && token[len - 1] == '"') {
        return token.substr(1, len - 2);
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
		return token.substr(1, len - 2);
	}
	else if (token == "_") {
		return token;
	}
	else if (qv.isSynonym(token)) {
		return stringToSynonym(token, synonymMap);
	}
	else {
		throw SemanticErrorException("Invalid synonym in clause");
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