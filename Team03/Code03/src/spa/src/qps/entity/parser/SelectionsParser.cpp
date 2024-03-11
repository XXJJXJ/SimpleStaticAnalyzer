#include "SelectionsParser.h"
#include "common/EntityType.h"
#include <memory>

SelectionsParser::SelectionsParser() = default;

SelectionsParser::~SelectionsParser() = default;

std::vector<std::shared_ptr<Synonym>>
SelectionsParser::parse(const std::vector<std::string> &tokens,
                        const std::unordered_map<std::string, EntityType> &synonymMap) {
    std::vector<std::shared_ptr<Synonym>> selections = {};

    for (const auto & token : tokens) {
        std::shared_ptr<Synonym> synonym = std::make_shared<Synonym>(token, synonymMap);
        selections.push_back(synonym);
    }

    return selections;
}