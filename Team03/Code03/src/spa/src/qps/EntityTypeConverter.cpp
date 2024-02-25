#include "EntityTypeConverter.h"

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/c3d59194-4f71-41b5-b045-642450edca7a

const std::unordered_map<std::string, EntityType> EntityTypeConverter::stringToEntityTypeMap = {
        {"stmt",      EntityType::Stmt},
        {"read",      EntityType::Read},
        {"print",     EntityType::Print},
        {"call",      EntityType::Call},
        {"while",     EntityType::While},
        {"if",        EntityType::If},
        {"assign",    EntityType::Assign},
        {"variable",  EntityType::Variable},
        {"constant",  EntityType::Constant},
        {"procedure", EntityType::Procedure}
};

const std::unordered_map<EntityType, std::string> EntityTypeConverter::entityTypeToStringMap;

bool EntityTypeConverter::initialized = initialize();

bool EntityTypeConverter::initialize() {
    for (const auto &pair: stringToEntityTypeMap) {
        entityTypeToStringMap[pair.second] = pair.first;
    }
    return true;
}

EntityType EntityTypeConverter::getEnumFromString(const std::string &s) {
    auto it = stringToEntityTypeMap.find(s);
    if (it != stringToEntityTypeMap.end()) {
        return it->second;
    } else {
        return EntityType::Unknown;
    }
}

std::string EntityTypeConverter::getStringFromEnum(EntityType e) {
    auto it = entityTypeToStringMap.find(e);
    if (it != entityTypeToStringMap.end()) {
        return it->second;
    } else {
        return "Unknown";
    }
}

// ai-gen end
