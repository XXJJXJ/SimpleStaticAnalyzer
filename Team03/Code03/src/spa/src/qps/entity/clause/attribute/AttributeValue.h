#ifndef ATTRIBUTE_VALUE_H
#define ATTRIBUTE_VALUE_H

#include <variant>
#include <string>
#include "../PredicateUtils.h"

using AttributeVariant = std::variant<int, std::string>;

// Wrapper class for extracted attribute values
class AttributeValue {
private:
    AttributeVariant value;
    AttributeValueType valueType;

public:
    AttributeValue(int intValue);
    AttributeValue(std::string stringValue);
    AttributeValueType getAttributeValueType() const;

    [[nodiscard]] bool equals(const AttributeValue &other) const;
    [[nodiscard]] std::string toString() const;
    std::size_t hash() const;
};

#endif // ATTRIBUTE_VALUE_H
