#include "AttrRef.h"
#include "qps/entity/clause/PredicateUtils.h"
#include "qps/entity/clause/attribute/StmtNumberExtractor.h"
#include "common/spa_exception/SemanticErrorException.h"

// Constructor definition
AttrRef::AttrRef(std::shared_ptr<Synonym> synonym, AttributeType attributeType)
    : synonym(std::move(synonym)), attributeType(attributeType) {
    if (!isValidAttributeType()) {
        throw SemanticErrorException("Invalid attribute type for the synonym used");
    }
    this->extractor = ExtractorFactory::createExtractor(attributeType);
}

// getSynonym method definition
std::shared_ptr<Synonym> AttrRef::getSynonym() const {
    return synonym;
}

AttributeType AttrRef::getAttributeType() const {
    return attributeType;
}
AttributeValueType AttrRef::getAttributeValueType() const {
    if (attributeType == AttributeType::ProcName || attributeType == AttributeType::VarName) {
        return AttributeValueType::Name;
    }
    return AttributeValueType::Integer;
}

AttributeValue AttrRef::extractAttribute(const Entity &entity) const {
    return extractor->extract(entity);
}

bool AttrRef::isValidAttributeType() {
    EntityType entityType = synonym->getType();
    if (VALID_ENTITY_TYPES_FOR_ATTRIBUTE.find(attributeType) == VALID_ENTITY_TYPES_FOR_ATTRIBUTE.end()) {
        return false;
    }
    return VALID_ENTITY_TYPES_FOR_ATTRIBUTE.at(attributeType).find(entityType)
        != VALID_ENTITY_TYPES_FOR_ATTRIBUTE.at(attributeType).end();
}

shared_ptr<AttributeExtractor> AttrRef::getExtractor() const {
    return extractor;
}

bool AttrRef::operator==(const AttrRef &other) const {
    return this->synonym == other.getSynonym() && this->getAttributeType() == other.getAttributeType();
}
std::size_t AttrRef::hash() const {
    return std::hash<Synonym>()(*synonym) ^ std::hash<AttributeType>()(attributeType);
}