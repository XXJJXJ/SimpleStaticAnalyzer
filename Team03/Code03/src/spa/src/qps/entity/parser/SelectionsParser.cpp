#include "SelectionsParser.h"
#include "common/EntityType.h"
#include <memory>

SelectionsParser::SelectionsParser() = default;

SelectionsParser::~SelectionsParser() = default;

std::vector<std::shared_ptr<Synonym>>
SelectionsParser::parse(const std::vector<std::string>& tokens,
    const std::unordered_map<std::string, EntityType>& synonymMap) {
    std::vector<std::shared_ptr<Synonym>> selections = {};

    if (!isBoolean(tokens, synonymMap)) {
        for (const auto& token : tokens) {
            std::shared_ptr<Synonym> synonym = std::make_shared<Synonym>(token, synonymMap);
            selections.push_back(synonym);
        }
    }
  
    return selections;
}

// Checks if BOOLEAN is a declared synonym
bool SelectionsParser::isBoolean(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap) {
    return tokens.size() == 1 && tokens[0] == "BOOLEAN" && synonymMap.count(tokens[0]) == 0;
}