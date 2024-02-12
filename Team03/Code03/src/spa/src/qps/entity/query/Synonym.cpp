#include "Synonym.h"

Synonym::Synonym(EntityType type, const std::string& name) {
    this->type = type;
    this->name = name;
}

EntityType Synonym::getType() const {
    return this->type;
}

const std::string& Synonym::getName() const {
    return this->name;
}

bool Synonym::operator==(const Synonym& other) const {
    return this->type == other.type && this->name == other.name;
}