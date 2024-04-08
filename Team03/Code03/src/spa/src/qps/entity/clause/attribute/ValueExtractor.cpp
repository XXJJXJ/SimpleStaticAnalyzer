#include "ValueExtractor.h"

AttributeValue ValueExtractor::extract(const Entity& entity) const {
    const auto* constant = dynamic_cast<const Constant*>(&entity);
    if (constant) {
        return {constant->getValue()};
    } else {
        // If the entity is not a Constant, throw an exception or return an error
        throw QPSEvaluationException("Entity is not a Constant");
    }
}
