/*
* Created by ZHENGTAO JIANG on 8/2/24.
*/

#include "QueryValidator.h"
#include "QueryParser.h"

QueryValidator::QueryValidator() {}
QueryValidator::~QueryValidator() {}

bool QueryValidator::validate(const std::string& parsedQuery)
{
    QueryParser qp;
    if (true) {
        //call main validation logic
        return true;
    }
    else {
        return false;
    }
}

bool QueryValidator::validateExpressionSpec(std::string expressionSpec)
{
    return true;
}
