#include "SelectionsParser.h"
#include "common/EntityType.h"

SelectionsParser::SelectionsParser() {}
SelectionsParser::~SelectionsParser() {}
std::vector<std::shared_ptr<Synonym>> SelectionsParser::parse(std::vector<std::string> tokens) {
    // Todo: implement
    std::vector<std::shared_ptr<Synonym>> selections = {};
    Synonym syn(EntityType::Variable, "variable");
    std::shared_ptr<Synonym> sharedSyn = std::make_shared<Synonym>(syn);
    selections.push_back(sharedSyn);

    return selections;
}