/*
* Created by ZHENGTAO JIANG on 8/2/24.
* 
* Given a string query, it checks if the query is valid based on the predefined PQL grammar
* If not valid, returns invalid query string
* If valid, continues execution by calling parseQuery
*/

#ifndef SPA_QUERYVALIDATOR_H
#define SPA_QUERYVALIDATOR_H
#include <string>

class QueryValidator {
public:
	QueryValidator();
	~QueryValidator();
	
	bool isLetter(const std::string& token);
	bool isDigit(const std::string& token);
	bool isNzDigit(const std::string& token);
	bool isIdent(const std::string& token);
	bool isName(const std::string& token);
	bool isInteger(const std::string& token);
	bool isSynonym(const std::string& token);
	bool isStmtRef(const std::string& token);
	bool isEntRef(const std::string& token);
};


#endif //SPA_QUERYVALIDATOR_H