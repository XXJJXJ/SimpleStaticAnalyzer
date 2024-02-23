#include <map>
#include <memory>
#include <string>
#include <vector>

#include "DeclarationsParser.h"
#include "common/EntityType.h"
#include "qps/QueryValidator.h"
#include <common/spa_exception/SemanticErrorException.h>
#include <common/spa_exception/SyntaxErrorException.h>

DeclarationsParser::DeclarationsParser() = default;

DeclarationsParser::~DeclarationsParser() {}

// ai-gen start (gpt, 1, e)
// prompt:
std::vector<std::shared_ptr<Synonym>>
DeclarationsParser::parse(const std::vector<std::string> &tokens,
                          std::unordered_map<std::string, EntityType> &synonymMap) {

    QueryValidator qv;
    std::vector<std::shared_ptr<Synonym>> declarations;

    // Try to parse first token as entity type
    EntityType currEntityType = mapTokenToEntityType(tokens[0]);

    // Invalid Entity Type or declaration doesn't start with an entity type
    if (currEntityType == EntityType::Unknown) {
        throw SyntaxErrorException("Syntax Error: Invalid Entity Type");
    };

    // Flag to check if next token should be a synonym name
    // Variable name expected after EntityType definition
    bool expectNameNext = true;

    // Iterate through the rest of the tokens, less the first (entity type) and last (semicolon)
    // Tokenizer ensures that the last token confirm is semicolon
    for (size_t i = 1; i < tokens.size() - 1; ++i) {
        if (tokens[i] == ",") {
            if (!expectNameNext) { // Found consecutive commas or a comma after an invalid token
                throw SyntaxErrorException("Syntax Error: Unexpected ',' in declaration");
            }
            expectNameNext = true; // Next token must be a valid synonym name
        } else {
            if (!expectNameNext) { // Did not find a comma where one was expected
                throw SyntaxErrorException("Syntax Error: Expected ',' between synonym names");
            }
            std::string name = tokens[i];
            if (synonymMap.find(name) != synonymMap.end()) {
                throw SemanticErrorException("Duplicate declaration of " + name);
            }

            if (!qv.isName(name)) { // Validate synonym name more rigorously
                throw SyntaxErrorException("Syntax Error: Invalid synonym name");
            }

            synonymMap[name] = currEntityType;
            declarations.push_back(std::make_shared<Synonym>(currEntityType, name));
            expectNameNext = false; // Reset flag since a valid name was found
        }
    }

    // Check if the declaration ended expecting a name
    // Cases: {"variable", "a", ",", ";" }
    if (expectNameNext) {
        throw SyntaxErrorException("Syntax Error: Incomplete declaration");
    }

    return declarations;
}
// ai-gen end

// ai-gen start (gpt, 0, e)
// prompt: https://chat.openai.com/share/4961f207-6946-4c80-8a64-e51b06b24aa1
EntityType DeclarationsParser::mapTokenToEntityType(const std::string &token) {
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