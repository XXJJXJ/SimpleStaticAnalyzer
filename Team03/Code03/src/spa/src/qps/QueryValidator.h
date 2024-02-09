/*
* Created by ZHENGTAO JIANG on 8/2/24.
* 
* Validates user query input based on "Basic PQL"
*/

#ifndef SPA_QUERYVALIDATOR_H
#define SPA_QUERYVALIDATOR_H
#include <string>

class QueryValidator {
public:
	bool validateQuery(std::string query);
	bool validateExpressionSpec(std::string expressionSpec);

};


#endif //SPA_QUERYVALIDATOR_H
