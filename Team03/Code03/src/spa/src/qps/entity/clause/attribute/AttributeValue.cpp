#include "AttributeValue.h"

AttributeValue::AttributeValue(int value) : value(value) {
    valueType = AttributeValueType::Integer;
}

AttributeValue::AttributeValue(std::string value) : value(value) {
    valueType = AttributeValueType::Name;
}

AttributeValueType AttributeValue::getAttributeValueType() const {
    return valueType;
}

bool AttributeValue::equals(const AttributeValue& other) const {
    return value == other.value;
}

std::string AttributeValue::toString() const {
    if (std::holds_alternative<int>(value)) {
        return std::to_string(std::get<int>(value));
    } else {
        return std::get<std::string>(value);
    }
}

std::size_t AttributeValue::hash() const {
    return std::hash<string>()(toString());
}