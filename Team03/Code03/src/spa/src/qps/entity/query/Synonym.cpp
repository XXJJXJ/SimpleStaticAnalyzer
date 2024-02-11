//
// Created by ZHENGTAO JIANG on 8/2/24.
//

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