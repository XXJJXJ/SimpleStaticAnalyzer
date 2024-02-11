/*
* Created by ZHENGTAO JIANG on 8/2/24.
*/

#include "QueryValidator.h"
#include "QueryParser.h"

std::string QueryValidator::validateQuery(std::string query)
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
