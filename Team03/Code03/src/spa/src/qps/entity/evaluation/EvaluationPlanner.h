#ifndef SPA_EVALUATIONPLANNER_H
#define SPA_EVALUATIONPLANNER_H

#include "qps/entity/query/Query.h"
#include "qps/QueryEvaluator.h"

class EvaluationPlanner {
private:
    shared_ptr<Query> query;
    shared_ptr<QueryEvaluator> evaluator;
public:
    EvaluationPlanner(shared_ptr<Query> query, shared_ptr<QueryEvaluator> evaluator);

    void plan();
private:
    void setSynonymGroups();
};

#endif //SPA_EVALUATIONPLANNER_H
