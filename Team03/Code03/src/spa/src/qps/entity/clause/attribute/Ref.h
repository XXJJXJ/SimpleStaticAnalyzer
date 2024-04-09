#pragma once

#include <string>
#include <variant>
#include "AttrRef.h"

using RefVariant = std::variant<std::string, int, AttrRef>;

class Ref {
private:
    RefVariant ref;

public:
    Ref(RefVariant ref) : ref(ref) {}
    AttributeValueType getAttributeValueType() const;
};