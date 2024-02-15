#include "SuchThatClause.h"
#include "qps/entity/strategy/Strategy.h"


std::vector<std::shared_ptr<Strategy>> SuchThatClause::getStrategies() const {
    std::vector<std::shared_ptr<Strategy>> strategies;
    strategies.reserve(predicates.size());
for (const auto& predicate : predicates) {
        // Based on predicate type, you would determine appropriate strategies
        // This is a simplified example where we just add an ExampleStrategy
        strategies.push_back((predicate->getStrategy()));
    }
    return strategies;
}

void SuchThatClause::addPredicate(std::unique_ptr<RelationshipPredicate> predicate) {
    predicates.push_back(std::move(predicate));
}
