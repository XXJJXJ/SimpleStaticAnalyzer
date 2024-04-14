#ifndef SPA_NAMEEXTRACTOR_H
#define SPA_NAMEEXTRACTOR_H
#include "AttributeExtractor.h"
#include "AttributeValue.h"
#include "common/Entity.h"

// The default extractor, that extracts the name of the entity
class NameExtractor : public AttributeExtractor {
public:
    [[nodiscard]] AttributeValue extract(const Entity &entity) const override;
};

#endif //SPA_NAMEEXTRACTOR_H
