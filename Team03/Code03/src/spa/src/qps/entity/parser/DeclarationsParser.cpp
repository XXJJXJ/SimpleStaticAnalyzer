#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "DeclarationsParser.h"
#include "common/EntityType.h"
#include <common/spa_exception/SyntaxErrorException.h>

DeclarationsParser::DeclarationsParser() {}
DeclarationsParser::~DeclarationsParser() {}

std::vector<std::shared_ptr<Synonym>>
DeclarationsParser::parse(std::vector<std::string> const& tokens,
                          std::unordered_map<std::string, EntityType>& synonymMap) {

    std::vector<std::shared_ptr<Synonym>> declarations;

    // ai-gen start(gpt, 0, e)
    // prompt: https://chat.openai.com/share/62ae2963-4d00-4650-813c-22cd668f5c1e

    // Iterate through tokens
    for (size_t i = 0; i < tokens.size(); ++i) {
        // Check if the token is a variable declaration
        if (tokens[i] == "variable") {
            // Check for syntax error if there's no variable name following "variable"
            if (i + 1 >= tokens.size() || tokens[i + 1] == "," || tokens[i + 1] == ";") {
                throw SyntaxErrorException("Variable name expected after 'variable'");
            }
            // Get the variable name
            std::string variableName = tokens[++i];

            // Check if the variable is already declared
            if (synonymMap.find(variableName) != synonymMap.end()) {
                throw SyntaxErrorException("Variable '" + variableName + "' already declared");
            }

            // Store the variable in the map
            synonymMap[variableName] = EntityType::Variable;

            // Create and store the Synonym
            declarations.push_back(std::make_shared<Synonym>(EntityType::Variable, variableName));

            // Check for ',' or ';' after the variable name
            if (i + 1 >= tokens.size() || (tokens[i + 1] != "," && tokens[i + 1] != ";")) {
                throw SyntaxErrorException("',' or ';' expected after variable declaration");
            }
            // Move to the next token
            ++i;
        } else if (tokens[i] == ";") { // Check for syntax error: unexpected ';'
            throw SyntaxErrorException("Unexpected ';'");
        }
    }

    // ai-gen end

    return declarations;
}