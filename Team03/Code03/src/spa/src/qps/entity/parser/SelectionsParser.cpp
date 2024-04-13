#include "SelectionsParser.h"
#include "common/EntityType.h"
#include "PredicateFactory.h"
#include <memory>

SelectionsParser::SelectionsParser() = default;

SelectionsParser::~SelectionsParser() = default;

std::vector<std::shared_ptr<AttrRef>> SelectionsParser::parse(
    const std::vector<std::string> &tokens, const std::unordered_map<std::string, EntityType> &synonymMap) {
    std::vector<std::shared_ptr<AttrRef>> selections = {};

    if (!isBoolean(tokens, synonymMap)) {
        for (const auto &token : tokens) {
            auto selection = PredicateFactory::createAttrRef(token, synonymMap);
            // convert to shared ptr
            selections.push_back(selection);
        }
    }

    return selections;
}

// Checks if BOOLEAN is a declared synonym
bool SelectionsParser::isBoolean(
    const std::vector<std::string> &tokens, const std::unordered_map<std::string, EntityType> &synonymMap) {
    return tokens.size() == 1 && tokens[0] == "BOOLEAN" && synonymMap.count(tokens[0]) == 0;
}