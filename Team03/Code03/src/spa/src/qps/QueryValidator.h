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
	std::string validateQuery(std::string query);
	bool validateExpressionSpec(std::string expressionSpec);

};


#endif //SPA_QUERYVALIDATOR_H
