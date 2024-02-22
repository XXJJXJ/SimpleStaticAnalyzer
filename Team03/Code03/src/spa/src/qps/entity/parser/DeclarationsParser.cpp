#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "DeclarationsParser.h"
#include "common/EntityType.h"
#include <common/spa_exception/SemanticErrorException.h>
#include <common/spa_exception/SyntaxErrorException.h>

DeclarationsParser::DeclarationsParser() {}
DeclarationsParser::~DeclarationsParser() {}

// ai-gen start (gpt, 1, e)
// prompt: https://chat.openai.com/share/82e2cd52-da0f-49d9-8032-25cca59e34b3
std::vector<std::shared_ptr<Synonym>>
DeclarationsParser::parse(const std::vector<std::string>& tokens,
                          std::unordered_map<std::string, EntityType>& synonymMap) {

    std::vector<std::shared_ptr<Synonym>> declarations;

    // Empty Declarations
    // Cases: {}, {"variable", ";"}
    if (tokens.empty() || tokens.size() < 2) {
        throw SyntaxErrorException(
            "Syntax Error: Declarations are empty or not enough synonyms declared");
    }

    // Try to parse first token as entity type
    EntityType currEntityType = mapTokenToEntityType(tokens[0]);

    // Invalid Entity Type or declaration doesn't start with an entity type
    if (currEntityType == EntityType::Unknown) {
        throw SyntaxErrorException("Syntax Error: Invalid Entity Type");
    };

    // Parse the rest of the tokens
    for (size_t i = 1; i < tokens.size(); ++i) {
        // ";" is the end of the declaration
        if (tokens[i] == ";") {
            break;
        } else if (tokens[i] != ",") { // Skip commas
            std::string name = tokens[i];
            if (synonymMap.find(name) != synonymMap.end()) {
                throw SemanticErrorException("Duplicate declaration of " + name);
            }

            synonymMap[name] = currEntityType; // Add to map

            declarations.push_back(
                std::make_shared<Synonym>(currEntityType, name)); // Add to declarations
        }
    }

    return declarations;
}
// ai-gen end

// ai-gen start (gpt, 0, e)
// prompt: https://chat.openai.com/share/4961f207-6946-4c80-8a64-e51b06b24aa1
EntityType DeclarationsParser::mapTokenToEntityType(const std::string& token) {
    // Implement mapping from token to EntityType
    if (token == "stmt") {
        return EntityType::Stmt;
    } else if (token == "read") {
        return EntityType::Read;
    } else if (token == "print") {
        return EntityType::Print;
    } else if (token == "call") {
        return EntityType::Call;
    } else if (token == "while") {
        return EntityType::While;
    } else if (token == "if") {
        return EntityType::If;
    } else if (token == "assign") {
        return EntityType::Assign;
    } else if (token == "variable") {
        return EntityType::Variable;
    } else if (token == "constant") {
        return EntityType::Constant;
    } else if (token == "procedure") {
        return EntityType::Procedure;
    } else {
        return EntityType::Unknown;
    }
}
// ai-gen end