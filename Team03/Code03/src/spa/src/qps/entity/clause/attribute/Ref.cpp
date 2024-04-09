#include "Ref.h"

AttributeValueType Ref::getAttributeValueType() const {
    if (std::holds_alternative<AttributeValue>(this->ref)) {
        return std::get<AttributeValue>(this->ref).getAttributeValueType();
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

AttributeValue Ref::getValue() const {
    if (!holdsSynonym()) {
        return std::get<AttributeValue>(this->ref);
    }
    throw QPSEvaluationException("Ref::getValue() called on synonym ref");
}

AttributeValue Ref::extractAttribute(Entity &entity) const {
    if (holdsSynonym()) {
        AttrRef attrRef = std::get<AttrRef>(this->ref);
        return attrRef.extractAttribute(entity);
    }
    throw QPSEvaluationException("Ref::extractAttribute() called on non-synonym ref");
}

