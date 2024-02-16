#include "Query.h"

vector<shared_ptr<Strategy>> Query::getStrategies() const{
    vector<shared_ptr<Strategy>> strategies;
    strategies.push_back(make_shared<DeclarationStrategy>(declarations));
    //strategies.push_back(make_shared<ProjectionStrategy>(selections));
    strategies.push_back(make_shared<ProjectionStrategy>(selections[0])); //temporary to compile
    return strategies;
}
