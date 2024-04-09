#include "NameExtractor.h"

AttributeValue NameExtractor::extract(const Entity& entity) const {
    return {entity.getName()};
}
