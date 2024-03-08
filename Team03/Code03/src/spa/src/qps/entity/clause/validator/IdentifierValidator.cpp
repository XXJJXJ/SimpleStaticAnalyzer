
#include "IdentifierValidator.h"
#include "common/Entity.h" // Assuming Entity class has getName() method

IdentifierValidator::IdentifierValidator(const std::string& identifier)
        : expectedIdentifier(identifier) {}

bool IdentifierValidator::validate(const std::shared_ptr<Entity>& entity) const {
    if (!entity) return false;
    return entity->getName() == expectedIdentifier;
}
