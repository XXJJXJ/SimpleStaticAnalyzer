#include <utility>

#include "AttributeFilter.h"

bool AttributeFilter::passFilter(const shared_ptr<Entity> &entity) const {
    auto extractedValue = extractor->extract(*entity);
    return extractedValue.equals(expectedValue);
}

AttributeFilter::AttributeFilter(AttributeValue expectedValue, std::shared_ptr<AttributeExtractor> extractor)
        : expectedValue(std::move(expectedValue)), extractor(std::move(extractor)) {}
