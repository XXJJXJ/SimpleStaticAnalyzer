#include "AttrRef.h"
#include "common/spa_exception/SemanticErrorException.h"

// Constructor definition
AttrRef::AttrRef(std::shared_ptr<Synonym> synonym, AttributeType attributeType, std::shared_ptr<AttributeExtractor> extractor)
        : synonym(std::move(synonym)), extractor(std::move(extractor)) {
    this->attributeType = attributeType;
    if (!isValidAttributeType()) {
        throw SemanticErrorException("Invalid attribute type for the synonym used");
    }
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


AttributeValue AttrRef::extractAttribute(const Entity& entity) const {
    return extractor->extract(entity);
}

bool AttrRef::isValidAttributeType() {
    EntityType entityType = synonym->getType();

    if (attributeType == AttributeType::ProcName) {
        return entityType == EntityType::Procedure || entityType == EntityType::Call;
    } else if (attributeType == AttributeType::VarName) {
        return entityType == EntityType::Variable || entityType == EntityType::Read || entityType == EntityType::Print;
    } else if (attributeType == AttributeType::Value) {
        return entityType == EntityType::Constant;
    } else if (attributeType == AttributeType::StmtNumber) {
        return VALID_STATEMENT_TYPES.find(entityType) != VALID_STATEMENT_TYPES.end();
    }

    return false;
}