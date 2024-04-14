#include "Synonym.h"
#include "common/spa_exception/SemanticErrorException.h"

Synonym::Synonym(EntityType type, const std::string &name) {
    this->type = type;
    this->name = name;
}

Synonym::Synonym(const std::string &synonymName, const std::unordered_map<std::string, EntityType> &synonymMap) {
    try {
        EntityType synonymType = synonymMap.at(synonymName);
        this->type = synonymType;
        this->name = synonymName;
    } catch (const std::out_of_range &e) {
        throw SemanticErrorException("Selected synonym '" + synonymName + "' has not been declared");
    }
}

EntityType Synonym::getType() const {
    return this->type;
}

const std::string &Synonym::getName() const {
    return this->name;
}

bool Synonym::operator==(const Synonym &other) const {
    return this->type == other.type && this->name == other.name;
}

