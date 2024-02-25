/*
 * Given a string, output the EntityType
 * given an EntityType, output the string
 */

#ifndef SPA_ENTITYTYPECONVERTER_H
#define SPA_ENTITYTYPECONVERTER_H

#include <unordered_map>
#include <string>
#include "common/EntityType.h"

// ai-gen start (gpt, 1, e)
// prompt: https://chat.openai.com/share/c3d59194-4f71-41b5-b045-642450edca7a
class EntityTypeConverter {

public:
    static EntityType getEnumFromString(const std::string &s);

    static std::string getStringFromEnum(EntityType e);

    static bool initialize();

private:
    static std::unordered_map<std::string, EntityType> stringToEntityTypeMap;
    static std::unordered_map<EntityType, std::string> entityTypeToStringMap;
    [[maybe_unused]] static bool initialized;
};
//ai-gen end

#endif //SPA_ENTITYTYPECONVERTER_H
