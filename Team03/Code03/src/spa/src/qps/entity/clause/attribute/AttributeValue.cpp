#include "AttributeValue.h"

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