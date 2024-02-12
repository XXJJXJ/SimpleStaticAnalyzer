//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#include "QueryEvaluator.h"


QueryEvaluator::QueryEvaluator() {
    // Create a context with the list of strategies
    context = std::make_shared<QueryEvaluationContext>();
}

//QueryEvaluator::~QueryEvaluator() {}

std::string QueryEvaluator::evaluate(const shared_ptr<Query>& query) {
    for (const auto& strategy : query->getStrategies()) {
        strategy->execute(*context);
    }
    return context->resultToString();
}