#ifndef VALUE_EXTRACTOR_H
#define VALUE_EXTRACTOR_H

#include "AttributeExtractor.h"
#include "AttributeValue.h"
#include "common/expression/Constant.h" // Include the Constant class definition

class ValueExtractor : public AttributeExtractor {
public:
    [[nodiscard]] AttributeValue extract(const Entity &entity) const override;
};

#endif // VALUE_EXTRACTOR_H
