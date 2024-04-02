#include "AttrRef.h"


// Constructor definition
AttrRef::AttrRef(std::shared_ptr<Synonym> synonym, std::shared_ptr<AttributeExtractor> extractor)
        : synonym(std::move(synonym)), extractor(std::move(extractor)) {}

// getSynonym method definition
std::shared_ptr<Synonym> AttrRef::getSynonym() const {
    return synonym;
}

AttributeValue AttrRef::extractAttribute(const Entity& entity) const {
    return extractor->extract(entity);
}

