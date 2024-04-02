#include "AttributeValue.h"

bool AttributeValue::equals(const AttributeValue& other) const {
    return value == other.value;
}
