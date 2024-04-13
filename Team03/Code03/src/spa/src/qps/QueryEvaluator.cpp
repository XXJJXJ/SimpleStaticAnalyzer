// ai-gen start(gpt, 0, e)
// prompt:  https://chat.openai.com/share/cc725a19-b2cb-4541-9910-0b2b77365e00

#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator() : context(std::make_shared<QueryEvaluationContext>()) {}

void QueryEvaluator::setStrategies(const std::vector<std::shared_ptr<Strategy>> &newStrategies) {
    strategies = newStrategies;
}

std::vector<std::string> QueryEvaluator::evaluate(const std::shared_ptr<Query> &query) {
    for (const auto &strategy : strategies) {
        strategy->execute(*context);
    }
    return context->getResults();
}

std::shared_ptr<QueryEvaluationContext> QueryEvaluator::getContext() const {
    return context;
}

// ai-gen end