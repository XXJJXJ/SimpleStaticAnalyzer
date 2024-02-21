#include "PredicateFactory.h"
#include "qps/QueryValidator.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/SemanticErrorException.h"

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
	else if (qv.isInteger(token)) {
		return stringToInteger(token);
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

int PredicateFactory::stringToInteger(const std::string& token) {
	return stoi(token);
}