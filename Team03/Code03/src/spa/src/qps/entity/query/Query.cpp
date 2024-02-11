#include "Query.h"

std::vector<std::shared_ptr<Strategy>> Query::getStrategies() {
    std::vector<std::shared_ptr<Strategy>> strategies;
    strategies.push_back(std::make_shared<DeclarationStrategy>(synonyms));
    return strategies;
}

