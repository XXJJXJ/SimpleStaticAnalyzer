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

bool Ref::holdsSynonym() const {
    if (std::holds_alternative<AttrRef>(this->ref)) {
        return true;
    }
    return false;
}

shared_ptr<Synonym> Ref::getSynonym() const {
    if (holdsSynonym()) {
        AttrRef attrRef = std::get<AttrRef>(this->ref);
        return attrRef.getSynonym();
    } else {
        throw QPSEvaluationException("Ref::getSynonym() called on non-synonym ref");
    }
}

RefVariant Ref::getValue() const {
    return RefVariant();
}
