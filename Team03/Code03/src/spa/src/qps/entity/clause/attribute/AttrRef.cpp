#include "AttrRef.h"
#include "qps/QueryValidator.h"
#include "qps/entity/clause/PredicateUtils.h"
#include "qps/entity/clause/attribute/ProcNameExtractor.h"
#include "qps/entity/clause/attribute/VarNameExtractor.h"
#include "qps/entity/clause/attribute/ValueExtractor.h"
#include "qps/entity/clause/attribute/StmtNumberExtractor.h"
#include "common/spa_exception/SemanticErrorException.h"

// Constructor definition
//AttrRef::AttrRef(std::shared_ptr<Synonym> synonym, AttributeType attributeType, std::shared_ptr<AttributeExtractor> extractor)
//        : synonym(std::move(synonym)), extractor(std::move(extractor)) {
//    this->attributeType = attributeType;
//    if (!isValidAttributeType()) {
//        throw SemanticErrorException("Invalid attribute type for the synonym used");
//    }
//}

// TODO: we're not supposed to do parsing in AttrRef constructor.
AttrRef::AttrRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap) {
    if (QueryValidator::isAttrRef(token)) {
        size_t pos = token.find('.');
        Synonym synonym(token.substr(0, pos), synonymMap);
        EntityType entityType = synonym.getType();
        AttributeType attributeType = getAttributeTypeFromString(token.substr(pos + 1));
        
        this->synonym = std::make_shared<Synonym>(synonym);
        this->attributeType = attributeType;

        if (!isValidAttributeType()) {
            throw SemanticErrorException("Invalid attribute type for the synonym used");
        }

        switch (attributeType) {
        case AttributeType::ProcName:
            this->extractor = std::make_shared<ProcNameExtractor>();
            break;
        case AttributeType::VarName:
            this->extractor = std::make_shared<VarNameExtractor>();
            break;
        case AttributeType::Value:
            this->extractor = std::make_shared<ValueExtractor>();
            break;
        case AttributeType::StmtNumber:
            this->extractor = std::make_shared<StmtNumberExtractor>();
            break;
        }
    } else {
        Synonym synonym(token, synonymMap);
        AttributeType attributeType = AttributeType::NoAttribute;

        this->synonym = std::make_shared<Synonym>(synonym);
        this->attributeType = attributeType;

        this->extractor = std::make_shared<NameExtractor>();
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

shared_ptr<AttributeExtractor> AttrRef::getExtractor() const {
    return extractor;
}