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

bool QueryValidator::isInteger(const std::string& token) {
	return true;
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
