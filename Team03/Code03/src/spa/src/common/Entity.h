#pragma once

#include "sp/design_extractor/Visitor.h"
#include <string>
#include "EntityType.h"

// In Entity.h
class Entity {
public:
    virtual void accept(std::shared_ptr<Visitor> visitor) = 0;
    virtual std::string getName() const = 0;
    virtual bool operator==(const Entity &other) const {
        return getName() == other.getName();
    }
    virtual bool operator!=(const Entity &other) const {
        return !(*this == other);
    }
    [[nodiscard]] virtual EntityType getType() const = 0;
    [[nodiscard]] virtual bool isOfType(EntityType type) const = 0;
    virtual bool operator<(const Entity &other) const {
        if (getType() != other.getType()) {
            return getType() < other.getType();
        }
        return getName() < other.getName();
    }
};

// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/327ddcad-1334-492d-998a-c324af935205
namespace std {
template<>
struct hash<Entity> {
    std::size_t operator()(const Entity &entity) const {
        // Combine hashes of the name and type
        std::size_t h1 = std::hash<std::string>()(entity.getName());
        std::size_t h2 = std::hash<int>()(static_cast<int>(entity.getType()));
        return h1 ^ (h2 << 1);
    }
};
}
// ai-gen end