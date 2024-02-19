#include "SelectionsParser.h"
#include "common/EntityType.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include <memory>

SelectionsParser::SelectionsParser() {}
SelectionsParser::~SelectionsParser() {}

std::vector<std::shared_ptr<Synonym>>
SelectionsParser::parse(const std::vector<std::string>& tokens,
                        const std::unordered_map<std::string, EntityType>& synonymMap) {
    std::vector<std::shared_ptr<Synonym>> selections = {};
    size_t len = tokens.size();

    // Select tuple
    if (tokens[1] == "<" && tokens[len - 1] == ">" && len > 3) {
        bool isSyn = true;
        // tokens within "<" and ">" must start and end with synonym, alternate between synonym and
        // ","
        for (size_t i = 2; i < len - 1; i++) {
            std::string token = tokens[i];
            if (isSyn) {
                std::shared_ptr<Synonym> synonym = makeSynonym(token, synonymMap);
                selections.push_back(synonym);
                isSyn = false;
            } else if (token == "," && i < len - 2) {
                isSyn = true;
            } else {
                throw SyntaxErrorException("Invalid selection syntax");
            }
        }
    }
    // Select a single synonym
    else if (len == 2) {
        std::shared_ptr<Synonym> synonym = makeSynonym(tokens[1], synonymMap);
        selections.push_back(synonym);
    } else {
        throw SyntaxErrorException("Invalid selection syntax");
    }

    return selections;
}

std::shared_ptr<Synonym>
SelectionsParser::makeSynonym(const std::string& synonymName,
                              const std::unordered_map<std::string, EntityType>& synonymMap) {
    try {
        EntityType synonymType = synonymMap.at(synonymName);
        std::shared_ptr<Synonym> synonym = std::make_shared<Synonym>(synonymType, synonymName);
        return synonym;
    } catch (const std::out_of_range& e) {
        throw SemanticErrorException("Selected synonym '" + synonymName +
                                     "' has not been declared");
    }
}