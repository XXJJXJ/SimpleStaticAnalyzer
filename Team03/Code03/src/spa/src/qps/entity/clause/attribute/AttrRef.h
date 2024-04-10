#ifndef ATTR_REF_H
#define ATTR_REF_H

#include <memory>
#include "AttributeExtractor.h"
#include "NameExtractor.h"
#include "qps/entity/query/Synonym.h"
#include "AttributeValue.h"
#include "qps/entity/clause/PredicateUtils.h"

class AttrRef {
private:
    std::shared_ptr<Synonym> synonym; // Shared pointer to a Synonym object
    std::shared_ptr<AttributeExtractor> extractor; // Shared pointer to the attribute extractor
    AttributeType attributeType;

    bool isValidAttributeType();

public:
    // Updated constructor to accept a shared_ptr<Synonym>
    //AttrRef(std::shared_ptr<Synonym> synonym, AttributeType attributeType, std::shared_ptr<AttributeExtractor> extractor);
    AttrRef(const std::string& token, const std::unordered_map<std::string, EntityType>& synonymMap);

    // Method to get the synonym
    std::shared_ptr<Synonym> getSynonym() const;
    
    AttributeType getAttributeType() const;
    AttributeValueType getAttributeValueType() const;

    AttributeValue extractAttribute(const Entity& entity) const;
    [[nodiscard]] shared_ptr<AttributeExtractor> getExtractor() const;
    bool operator==(const AttrRef &other) const;
    std::size_t hash() const;
};

#endif // ATTR_REF_H
