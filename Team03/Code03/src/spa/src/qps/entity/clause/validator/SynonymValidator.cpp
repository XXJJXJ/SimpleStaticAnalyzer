// SynonymTypeValidator.cpp

#include "SynonymValidator.h"
#include "common/Entity.h" // Assuming Statement class has isOfType method

SynonymValidator::SynonymValidator(const Synonym& synonym)
        : expectedType(synonym.getType()) {}

bool SynonymValidator::validate(const std::shared_ptr<Entity>& entity) const {
    return entity != nullptr && entity->isOfType(expectedType);
}
