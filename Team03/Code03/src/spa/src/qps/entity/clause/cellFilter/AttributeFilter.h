#ifndef SPA_ATTRIBUTEFILTER_H
#define SPA_ATTRIBUTEFILTER_H

#include <string>
#include <variant>
#include "qps/entity/clause/attribute/Ref.h"
#include "qps/entity/clause/PredicateUtils.h"
#include "CellFilter.h"

class AttributeFilter : public CellFilter {
private:
    AttributeValue expectedValue;
    shared_ptr<AttributeExtractor> extractor;
public:
    AttributeFilter(AttributeValue expectedValue, shared_ptr<AttributeExtractor> extractor);
    bool passFilter(const std::shared_ptr<Entity> &entity) const override;
};

#endif //SPA_ATTRIBUTEFILTER_H
