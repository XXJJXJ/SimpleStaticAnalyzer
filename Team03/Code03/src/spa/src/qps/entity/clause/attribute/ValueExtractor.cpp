#include "ValueExtractor.h"

AttributeValue ValueExtractor::extract(const Entity& entity) const {
    const auto* constant = dynamic_cast<const Constant*>(&entity);
    if (constant) {
        return {constant->getName()}; // TODO: HOW TO GET INT FROM CONSTANT???
    } else {
        // If the entity is not a Constant, throw an exception or return an error
        throw std::runtime_error("Entity is not a Constant");
    }
}
