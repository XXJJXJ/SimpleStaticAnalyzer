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

bool Ref::operator==(const Ref &other) const {
    if (this->holdsSynonym() && other.holdsSynonym()) {
        AttrRef attrRef = std::get<AttrRef>(this->ref);
        AttrRef otherAttrRef = std::get<AttrRef>(other.ref);
        return attrRef == otherAttrRef;
    } else if (std::holds_alternative<AttributeValue>(this->ref) && std::holds_alternative<AttributeValue>(other.ref)) {
        return this->getValue().equals(other.getValue());
    } else {
        // diff types
        return false;
    }
}

std::size_t Ref::hash() const {
    if (this->holdsSynonym()) {
        return std::get<AttrRef>(this->ref).hash();
    } else {
        return this->getValue().hash();
    }
}

