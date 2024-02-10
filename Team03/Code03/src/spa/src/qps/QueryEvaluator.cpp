//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#include "QueryEvaluator.h"


QueryEvaluator::QueryEvaluator(const Query& query) {
    // Initialize the list of strategies based on the query
    std::vector<std::shared_ptr<Strategy>> strategies = query.getStrategies();

    // Create a context with the list of strategies
    context = std::make_shared<QueryEvaluationContext>(strategies);
}

QueryEvaluator::~QueryEvaluator() {}

std::string QueryEvaluator::evaluate(const std::string& validatedQuery) {
    // Basic evaluation logic

    return validatedQuery;
}