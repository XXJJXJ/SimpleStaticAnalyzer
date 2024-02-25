#include <map>
#include <memory>
#include <string>
#include <vector>

#include "DeclarationsParser.h"
#include "common/EntityType.h"
#include "qps/QueryValidator.h"
#include "qps/util/EntityTypeConverter.h"
#include <common/spa_exception/SemanticErrorException.h>
#include <common/spa_exception/SyntaxErrorException.h>

DeclarationsParser::DeclarationsParser() = default;

DeclarationsParser::~DeclarationsParser() = default;

// ai-gen start (gpt, 1, e)
// prompt 1: https://chat.openai.com/share/82e2cd52-da0f-49d9-8032-25cca59e34b3
// prompt 2: https://chat.openai.com/share/d86b9515-ec39-46ef-aaae-c8e284de92a2
std::vector<std::shared_ptr<Synonym>>
DeclarationsParser::parse(const std::vector<std::string> &tokens,
                          std::unordered_map<std::string, EntityType> &synonymMap) {

    std::vector<std::shared_ptr<Synonym>> declarations;

    // Try to parse first token as entity type
    EntityType currEntityType = EntityTypeConverter::getEnumFromString(tokens[0]);

    // Invalid Entity Type or declaration doesn't start with an entity type
    if (currEntityType == EntityType::Unknown) {
        throw SyntaxErrorException("Syntax Error: Invalid Entity Type");
    }

    // Flag to check if next token should be a synonym name
    // Variable name expected after EntityType definition
    bool expectNameNext = true;


    // Iterate through the rest of the tokens, less the first (entity type) and last (semicolon)
    // Tokenizer ensures that the last token confirm is semicolon
    for (size_t i = 1; i < tokens.size() - 1; ++i) {
        if (tokens[i] == ",") {
            if (expectNameNext) { // Found consecutive commas or a comma after an invalid token
                throw SyntaxErrorException("Syntax Error: Unexpected ',' in declaration");
            }
            expectNameNext = true; // Next token must be a valid synonym name
        } else {
            if (!expectNameNext) { // Did not find a comma where one was expected
                throw SyntaxErrorException("Expected ',' between synonym names");
            }
            std::string name = tokens[i];
            if (synonymMap.find(name) != synonymMap.end()) {
                throw SemanticErrorException("Duplicate declaration of " + name);
            }

            if (!QueryValidator::isName(name)) { // Validate synonym name more rigorously
                throw SyntaxErrorException("Invalid synonym name");
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