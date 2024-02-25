#pragma once

#include "sp/design_extractor/Visitor.h"
#include <string>
#include "EntityType.h"

// In Entity.h
class Entity {
public:
    virtual void accept(std::shared_ptr<Visitor> visitor) = 0;
    virtual std::string getName() const = 0;
    virtual bool operator==(const Entity& other) const {
        return getName() == other.getName();
    }
    virtual bool operator!=(const Entity& other) const {
        return !(*this == other);
    }
    [[nodiscard]] virtual EntityType getType() const = 0;
    [[nodiscard]] virtual bool isOfType(EntityType type) const = 0;
};