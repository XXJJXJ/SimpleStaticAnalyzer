//
// Created by ZHENGTAO JIANG on 23/2/24.
//

#include "EvaluationPlanner.h"
#include "SynonymGraph.h"

#include <utility>

EvaluationPlanner::EvaluationPlanner(shared_ptr<Query> query, shared_ptr<QueryEvaluator> evaluator) {
    this->query = std::move(query);
    this->evaluator = std::move(evaluator);
}

// Plans the evaluation strategies, and updates the evaluator accordingly.
void EvaluationPlanner::plan() {

    // step 1: set synonym groups
    setSynonymGroups();

    // step 2: set strategies

}

void EvaluationPlanner::setSynonymGroups() {
    SynonymGraph graph = SynonymGraph(query->getPredicates());
    auto synonymGroups = graph.groupSynonyms();
    evaluator->getContext()->setSynonymGroups(synonymGroups);
}