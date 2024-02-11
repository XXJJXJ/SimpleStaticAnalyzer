/*
* Created by ZHENGTAO JIANG on 8/2/24.
*/

#include "QueryValidator.h"
#include "QueryParser.h"

QueryValidator::QueryValidator() {}
QueryValidator::~QueryValidator() {}

std::string QueryValidator::validate(const std::string& parsedQuery)
{
    QueryParser qp;
    if (true) {
        //call main validation logic
        //if valid it should call the query parser
        return qp.parseQuery(query);
    }
    else {
        return "Invalid Query";
    }
}

bool QueryValidator::validateExpressionSpec(std::string expressionSpec)
{
    return true;
}
