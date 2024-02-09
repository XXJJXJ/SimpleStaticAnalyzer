//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_QUERYVALIDATOR_H
#define SPA_QUERYVALIDATOR_H

#include <string>

class QueryValidator {
public:
    QueryValidator();

    ~QueryValidator();

    bool validate(const std::string& parsedQuery);
};


#endif //SPA_QUERYVALIDATOR_H
