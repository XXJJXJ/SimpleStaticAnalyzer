#include "Query.h"

vector<shared_ptr<Strategy>> Query::getStrategies() const{
    vector<shared_ptr<Strategy>> strategies;
    strategies.push_back(make_shared<DeclarationStrategy>(synonyms));
    return strategies;
}
