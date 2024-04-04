#include "Ref.h"

AttributeValueType Ref::getAttributeValueType() const {
    if (std::holds_alternative<int>(this->ref)) {
        return AttributeValueType::Integer;
    } else if (std::holds_alternative<std::string>(this->ref)) {
        return AttributeValueType::Name;
    } else {
        AttrRef attrRef = std::get<AttrRef>(this->ref);
        return attrRef.getAttributeValueType();
    }
}