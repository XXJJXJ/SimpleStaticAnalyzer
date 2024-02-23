/*
* Created by ZHENGTAO JIANG on 8/2/24.
*/

#include "QueryValidator.h"
#include "QueryParser.h"

QueryValidator::QueryValidator() {}
QueryValidator::~QueryValidator() {}

bool QueryValidator::isLetter(const std::string& token) {
	return true;
}

bool QueryValidator::isDigit(const std::string& token) {
	return true;
}

bool QueryValidator::isNzDigit(const std::string& token) {
	return true;
}

bool QueryValidator::isIdent(const std::string& token) {
	return true;
}

bool QueryValidator::isName(const std::string& token) {
	return true;
}

//Temp one for PredicateFactory to work
bool QueryValidator::isInteger(const std::string& token) {
	try {
		size_t pos;
		std::stoi(token, &pos);
		return pos == token.length() && token[0] != '0';  // Check if the entire string was consumed
	}
	catch (...) {
		return false;  // std::invalid_argument or std::out_of_range
	}
}

bool QueryValidator::isSynonym(const std::string& token) {
	return true;
}

bool QueryValidator::isStmtRef(const std::string& token) {
	return true;
}

bool QueryValidator::isEntRef(const std::string& token) {
	return true;
}
