#include "SynonymFilter.h"
#include "common/Entity.h"

SynonymFilter::SynonymFilter(const Synonym &synonym)
    : expectedType(synonym.getType()) {}

bool SynonymFilter::passFilter(const std::shared_ptr<Entity> &entity) const {
    return entity != nullptr && entity->isOfType(expectedType);
}
