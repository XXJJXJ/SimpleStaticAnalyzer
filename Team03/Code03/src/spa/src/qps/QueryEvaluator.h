//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H

#include <string>

class QueryEvaluator {
public:
    QueryEvaluator();

    ~QueryEvaluator();

    std::string evaluate(const std::string& validatedQuery);
};


#endif //SPA_QUERYEVALUATOR_H
