#include <map>
#include <memory>
#include <string>
#include <vector>

#include "DeclarationsParser.h"
#include "common/EntityType.h"
#include "qps/util/EntityTypeConverter.h"
#include <common/spa_exception/SemanticErrorException.h>

DeclarationsParser::DeclarationsParser() = default;

DeclarationsParser::~DeclarationsParser() = default;

std::vector<std::shared_ptr<Synonym>> DeclarationsParser::parse(
    const std::vector<std::string> &tokens, std::unordered_map<std::string, EntityType> &synonymMap) {

    std::vector<std::shared_ptr<Synonym>> declarations;

    EntityType currEntityType = EntityTypeConverter::getEnumFromString(tokens[0]);

    for (size_t i = 1; i < tokens.size(); i++) {
        std::string name = tokens[i];
        if (synonymMap.find(name) != synonymMap.end()) {
            throw SemanticErrorException("Duplicate declaration of " + name);
        }
        synonymMap[name] = currEntityType;
        declarations.push_back(std::make_shared<Synonym>(currEntityType, name));
    }

    return declarations;
}