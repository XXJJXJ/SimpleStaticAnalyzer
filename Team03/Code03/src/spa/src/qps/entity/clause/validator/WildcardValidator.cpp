#include "WildcardValidator.h"

bool WildcardValidator::validate(const std::shared_ptr<Entity>& entity) const {
    return entity != nullptr;
}
