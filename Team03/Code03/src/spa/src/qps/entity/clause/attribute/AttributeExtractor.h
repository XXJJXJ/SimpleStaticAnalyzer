#ifndef ATTRIBUTE_EXTRACTOR_H
#define ATTRIBUTE_EXTRACTOR_H

#include "common/Entity.h"
#include "AttributeValue.h"
#include "common/spa_exception/QPSEvaluationException.h"

class AttributeExtractor {
public:
    virtual ~AttributeExtractor() = default;
    [[nodiscard]] virtual AttributeValue extract(const Entity &entity) const = 0;
};

#endif // ATTRIBUTE_EXTRACTOR_H
