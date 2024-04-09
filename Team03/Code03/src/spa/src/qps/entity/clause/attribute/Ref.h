#pragma once

#include <string>
#include <utility>
#include <variant>
#include "AttrRef.h"

using RefVariant = std::variant<AttributeValue, AttrRef>;

class Ref {
private:
    RefVariant ref;

public:
    explicit Ref(RefVariant ref) : ref(std::move(ref)) {}
    AttributeValueType getAttributeValueType() const;
    bool holdsSynonym() const;
    shared_ptr<Synonym> getSynonym() const;
    AttributeValue getValue() const;
    AttributeValue extractAttribute(Entity& entity) const;
};