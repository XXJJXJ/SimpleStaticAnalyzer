//
// Created by ZHENGTAO JIANG on 8/2/24.
//
#ifndef SPA_QUERYEVALUATOR_H
#define SPA_QUERYEVALUATOR_H

#include <string>
#include <memory>
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/query/Query.h"
using namespace std;

class QueryEvaluator {
private:
    shared_ptr<QueryEvaluationContext> context;
public:
    QueryEvaluator(const shared_ptr<Query> query);

//    ~QueryEvaluator();

    std::string evaluate(const shared_ptr<Query>& query);
};


#endif //SPA_QUERYEVALUATOR_H
