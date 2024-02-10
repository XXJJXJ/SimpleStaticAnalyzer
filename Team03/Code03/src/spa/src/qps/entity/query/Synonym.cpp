//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#include "Synonym.h"

Synonym::Synonym(DesignEntityType type, const std::string& name) {
    this->type = type;
    this->name = name;
}

DesignEntityType Synonym::getType() const {
    return this->type;
}

const std::string& Synonym::getName() const {
    return this->name;
}