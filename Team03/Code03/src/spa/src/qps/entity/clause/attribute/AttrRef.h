#ifndef ATTR_REF_H
#define ATTR_REF_H

#include <memory>
#include "AttributeExtractor.h"
#include "qps/entity/query/Synonym.h"
#include "AttributeValue.h"

class AttrRef {
private:
    std::shared_ptr<Synonym> synonym; // Shared pointer to a Synonym object
    std::shared_ptr<AttributeExtractor> extractor; // Shared pointer to the attribute extractor

public:
    // Updated constructor to accept a shared_ptr<Synonym>
    AttrRef(std::shared_ptr<Synonym> synonym, std::shared_ptr<AttributeExtractor> extractor);

    // Method to get the synonym
    std::shared_ptr<Synonym> getSynonym() const;

    AttributeValue extractAttribute(const Entity& entity) const;
};

#endif // ATTR_REF_H
