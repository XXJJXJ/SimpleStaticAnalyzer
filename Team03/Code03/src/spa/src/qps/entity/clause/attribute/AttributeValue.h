#ifndef ATTRIBUTE_VALUE_H
#define ATTRIBUTE_VALUE_H

#include <variant>
#include <string>

using AttributeVariant = std::variant<int, std::string>;

// Wrapper class for extracted attribute values
class AttributeValue {
private:
    AttributeVariant value;

public:
    AttributeValue(int intValue) : value(intValue) {}
    AttributeValue(std::string stringValue) : value(std::move(stringValue)) {}

    [[nodiscard]] bool equals(const AttributeValue& other) const;
    [[nodiscard]] std::string toString() const;
};

#endif // ATTRIBUTE_VALUE_H
