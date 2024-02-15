// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/649c7ba0-9712-44e7-aa24-ca6262c5a922
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

void SuchThatClause::addPredicate(std::unique_ptr<Predicate> predicate) {
    predicates.push_back(std::move(predicate));
}
// ai-gen end