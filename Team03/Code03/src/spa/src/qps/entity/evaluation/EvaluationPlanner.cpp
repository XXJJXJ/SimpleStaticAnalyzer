#include "EvaluationPlanner.h"
#include "SynonymGraph.h"
#include "qps/entity/strategy/JoinWithPredicateStrategy.h"
#include "qps/entity/strategy/ProjectionStrategy.h"

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
    // Grouping and ordering within group not implemented yet, but it should work fine (just less efficient).
    vector<shared_ptr<Strategy>> strategies;
    for (auto& predicate : query->getPredicates()) {
        auto strategy = make_shared<JoinWithPredicateStrategy>(predicate);
        strategies.push_back(strategy);
    }
    // Projection strategy, only one selection is supported for now due to the implementation of the ProjectionStrategy.

    strategies.push_back(make_shared<ProjectionStrategy>(query->getSelectedSynonyms()));

    evaluator->setStrategies(strategies);

    // Step 3: set selected attributes
    evaluator->getContext()->setSelectedAttributes(query->getSelectedAttributes());

}

void EvaluationPlanner::setSynonymGroups() {
    SynonymGraph graph = SynonymGraph(query->getPredicates(), query->getDeclarations());
    auto synonymGroups = graph.groupSynonyms();
    evaluator->getContext()->setSynonymGroups(synonymGroups);
}