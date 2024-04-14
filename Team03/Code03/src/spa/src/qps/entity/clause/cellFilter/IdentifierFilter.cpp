#include "IdentifierFilter.h"
#include "common/Entity.h" // Assuming Entity class has getName() method

IdentifierFilter::IdentifierFilter(const std::string &identifier) : expectedIdentifier(identifier) {}

bool IdentifierFilter::passFilter(const std::shared_ptr<Entity> &entity) const {
    if (!entity) return false;
    return entity->getName() == expectedIdentifier;
}
