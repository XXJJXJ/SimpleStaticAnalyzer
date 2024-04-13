#include "QueryValidator.h"
#include <algorithm>
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/EntityType.h"
#include "qps/util/EntityTypeConverter.h"
#include "qps/util/QueryTokenValidator.h"
#include "qps/entity/clause/PredicateUtils.h"

QueryValidator::QueryValidator() = default;
QueryValidator::~QueryValidator() = default;

// Takes in tokens, validates them for syntax errors, then returns a simplified list of tokens (without unnecessary punctuation marks etc.) to be parsed by QueryParser
std::vector<std::vector<std::vector<std::string>>> QueryValidator::validate(const std::vector<std::string>& tokens) {
    std::vector<std::vector<std::vector<std::string>>> validatedQuery;

    std::vector<std::vector<std::vector<std::string>>> splitTokensList = splitTokens(tokens);

    std::vector<std::vector<std::string>> declarationsTokens = splitTokensList[0];
    std::vector<std::vector<std::string>> selectionsTokens = splitTokensList[1];
    std::vector<std::vector<std::string>> predicateTokens = splitTokensList[2];

    if (selectionsTokens.empty()) {
        throw SyntaxErrorException("No selections made");
    }

    std::vector<std::vector<std::string>> validatedDeclarationsTokens;
    std::vector<std::vector<std::string>> validatedSelectionsTokens;
    std::vector<std::vector<std::string>> validatedPredicateTokens;

    validatedDeclarationsTokens.reserve(declarationsTokens.size());
    validatedSelectionsTokens.reserve(selectionsTokens.size());
    validatedPredicateTokens.reserve(predicateTokens.size());

    for (std::vector<std::string>& declaration : declarationsTokens) {
        validatedDeclarationsTokens.push_back(validateDeclaration(declaration));
    }

    for (std::vector<std::string>& selection : selectionsTokens) {
        validatedSelectionsTokens.push_back(validateSelection(selection));
    }

    ClauseType prevClause = ClauseType::Invalid;
    for (std::vector<std::string>& predicate : predicateTokens) {
        validatedPredicateTokens.push_back(validatePredicate(predicate, prevClause));
    }

    validatedQuery.push_back(validatedDeclarationsTokens);
    validatedQuery.push_back(validatedSelectionsTokens);
    validatedQuery.push_back(validatedPredicateTokens);

    return validatedQuery;
}

std::vector<std::vector<std::vector<std::string>>> QueryValidator::splitTokens(const std::vector<std::string>& tokens) {
    std::vector<std::string> currentList;

    std::vector<std::vector<std::vector<std::string>>> splitTokens = {};
    std::vector<std::vector<std::string>> declarations;
    std::vector<std::vector<std::string>> selections;
    std::vector<std::vector<std::string>> clauses;

    bool isClause = false;

    for (const auto& token : tokens) {
        currentList.push_back(token);
        size_t currSize = currentList.size();

        if (token == ")" || (currSize > 2 && currentList[currSize - 2] == "=")) {
            if (!isClause) {
                throw SyntaxErrorException("Incorrect order in query");
            }
            clauses.push_back(currentList);
            currentList.clear();
        } else if (token == ";") {
            if (isClause) {
                throw SyntaxErrorException("Incorrect order in query");
            }
            declarations.push_back(currentList);
            currentList.clear();
        } else if (token == ">" && currentList[0] == "Select") {
            if (isClause) {
                throw SyntaxErrorException("Incorrect order in query");
            }
            selections.push_back(currentList);
            currentList.clear();
            isClause = true;
        } else if (currSize == 2 && currentList[0] == "Select" && token != "<") {
            // If the list starts with "Select", and the next token is not "<", end the list
            if (isClause) {
                throw SyntaxErrorException("Incorrect order in query");
            }
            selections.push_back(currentList);
            currentList.clear();
            isClause = true;
        }
    }

    if (!currentList.empty()) {
        clauses.push_back(currentList);;
    }

    splitTokens.push_back(declarations);
    splitTokens.push_back(selections);
    splitTokens.push_back(clauses);

    return splitTokens;
}


// Validates declaration, and returns a vector of strings with the first element as entity type and subsequent elements as names
// e.g. {"variable", "a", ",", "b", ",", "c", ";"} returns {"variable", "a", "b", "c"}
std::vector<std::string> QueryValidator::validateDeclaration(const std::vector<std::string>& tokens) {
    std::vector<std::string> validatedTokens;

    EntityType entityType = EntityTypeConverter::getEnumFromString(tokens[0]);

    if (entityType == EntityType::Unknown) {
        throw SyntaxErrorException("Syntax Error: Invalid Entity Type");
    }

    validatedTokens.push_back(tokens[0]);

    bool expectNameNext = true;

    for (size_t i = 1; i < tokens.size() - 1; i++) {
        if (tokens[i] == ",") {
            if (expectNameNext) { // Found consecutive commas or a comma after an invalid token
                throw SyntaxErrorException("Syntax Error: Unexpected ',' in declaration");
            }
            expectNameNext = true; // Next token must be a valid synonym name
        } else {
            if (!expectNameNext) { // Did not find a comma where one was expected
                throw SyntaxErrorException("Expected ',' between synonym names");
            }
            const std::string& name = tokens[i];

            if (!QueryTokenValidator::isName(name)) { // Validate synonym name more rigorously
                throw SyntaxErrorException("Invalid synonym name " + name);
            }

            validatedTokens.push_back(name);
            expectNameNext = false; // Reset flag since a valid name was found
        }
    }

    // Check if the declaration ended expecting a name
    // Cases: {"variable", "a", ",", ";" }
    if (expectNameNext) {
        throw SyntaxErrorException("Syntax Error: Incomplete declaration");
    }

    return validatedTokens;
}

// Validates selection, and returns a vector of strings with elements as names
// e.g. {"Select", "a"} returns {"a"}
// e.g. {"Select", "<", "a", ",", "b", ",", "c", ">"} returns {"a", "b", "c"}
std::vector<std::string> QueryValidator::validateSelection(const std::vector<std::string>& tokens) {
    std::vector<std::string> validatedTokens;

    size_t len = tokens.size();
    // Select tuple
    if (tokens[1] == "<" && tokens[len - 1] == ">" && len > 3) {
        bool isSyn = true;
        // tokens within "<" and ">" must start and end with synonym, alternate between synonym and ","
        for (size_t i = 2; i < len - 1; i++) {
            const std::string &token = tokens[i];
            if (isSyn) {
                if (!QueryTokenValidator::isName(token) && !QueryTokenValidator::isAttrRef(token)) {
                    throw SyntaxErrorException("Invalid synonym name " + token);
                }
                validatedTokens.push_back(token);
                isSyn = false;
            } else if (token == "," && i < len - 2) {
                isSyn = true;
            } else {
                throw SyntaxErrorException("Invalid selection syntax");
            }
        }
    } else if (len == 2) {
        const std::string &token = tokens[1];
        if (!QueryTokenValidator::isName(token) && !QueryTokenValidator::isAttrRef(token)) {
            throw SyntaxErrorException("Invalid synonym name " + token);
        }
        validatedTokens.push_back(token);
    } else {
        throw SyntaxErrorException("Invalid selection syntax");
    }

    return validatedTokens;
}

// Validates predicate, and returns a vector of strings with the first element as predicate type, and subsequent elements as arguments
// e.g. {"such", "that", "Follows", "(", "a", ",", "b", ")"} returns {"Follows", "a", "b"}
// e.g. {"pattern", "a", "(", "_", ",", "_", ")"} returns {"pattern", "a", "_", "_"}
std::vector<std::string> QueryValidator::validatePredicate(const std::vector<std::string>& tokens, ClauseType& prevClause) {
    ClauseType predType = getClauseType(tokens);

    switch (predType) {
    case ClauseType::SuchThat: {
        prevClause = ClauseType::SuchThat;
        std::vector<std::string> predicateTokens(tokens.begin() + 2, tokens.end());
        return validateSuchThatPredicate(predicateTokens);
    } case ClauseType::Pattern: {
        prevClause = ClauseType::Pattern;
        std::vector<std::string> predicateTokens(tokens.begin() + 1, tokens.end());
        return validatePatternPredicate(predicateTokens);
    } case ClauseType::With: {
        prevClause = ClauseType::With;
        std::vector<std::string> predicateTokens(tokens.begin() + 1, tokens.end());
        return validateWithPredicate(predicateTokens);
    } case ClauseType::And: {
        std::vector<std::string> predicateTokens(tokens.begin() + 1, tokens.end());
        switch (prevClause) {
        case ClauseType::SuchThat:
            return validateSuchThatPredicate(predicateTokens);
        case ClauseType::Pattern:
            return validatePatternPredicate(predicateTokens);
        case ClauseType::With:
            return validateWithPredicate(predicateTokens);
        default:
            throw SyntaxErrorException("Invalid use of and keyword");
        }
    } default: {
        throw SyntaxErrorException("Invalid clause keyword");
    }
    }
}

ClauseType QueryValidator::getClauseType(const std::vector<std::string>& tokens) {
    if (tokens.size() > 3 && tokens[0] == "such" && tokens[1] == "that") {
        return ClauseType::SuchThat;
    } else if (tokens.size() > 2 && tokens[0] == "pattern") {
        return ClauseType::Pattern;
    } else if (tokens.size() > 2 && tokens[0] == "with") {
        return ClauseType::With;
    } else if (tokens.size() > 2 && tokens[0] == "and") {
        return ClauseType::And;
    } else {
        return ClauseType::Invalid;
    }
}

std::vector<std::string> QueryValidator::validateSuchThatPredicate(const std::vector<std::string>& tokens) {
    if (isNotPredicate(tokens)) {
        std::vector<std::string> predicateTokens(tokens.begin() + 1, tokens.end());
        std::vector<std::string> validatedTokens = validateSuchThatPredicate(predicateTokens);
        validatedTokens.insert(validatedTokens.begin(), "not");
        return validatedTokens;
    }

    PredicateType predicateType = getPredicateType(tokens[0]);
    switch (predicateType) {
    case PredicateType::Affects:
    case PredicateType::Follows:
    case PredicateType::FollowsT:
    case PredicateType::Parent:
    case PredicateType::ParentT:
    case PredicateType::Next:
    case PredicateType::NextT:
        return validateStatementStatementPredicate(tokens);
    case PredicateType::Modifies:
    case PredicateType::Uses:
        return validateStmtEntEntityPredicate(tokens);
    case PredicateType::Calls:
    case PredicateType::CallsT:
        return validateEntityEntityPredicate(tokens);
    default:
        throw SyntaxErrorException("Invalid such that clause keyword " + tokens[0]);
    }
}

// For relationships between statements, i.e. Follows, FollowsT, Parent, ParentT
std::vector<std::string> QueryValidator::validateStatementStatementPredicate(const std::vector<std::string>& tokens) {
    const std::string& predicateType = tokens[0];

    if (isValidPredicateArgsNum(tokens, 2)) {
        std::vector<std::string> validatedTokens = getPredicateArgs(tokens, 2);
        if (!QueryTokenValidator::isStmtRef(validatedTokens[1]) || !QueryTokenValidator::isStmtRef(validatedTokens[2])) {
            throw SyntaxErrorException("Invalid " + predicateType + " clause arguments");
        }
        return validatedTokens;
    } else {
        throw SyntaxErrorException("Invalid " + predicateType + " clause syntax");
    }
}

// For relationships between statements/entities and entities, i.e. Modifies, Uses
std::vector<std::string> QueryValidator::validateStmtEntEntityPredicate(const std::vector<std::string>& tokens) {
    const std::string& predicateType = tokens[0];

    if (isValidPredicateArgsNum(tokens, 2)) {
        std::vector<std::string> validatedTokens = getPredicateArgs(tokens, 2);
        if (!QueryTokenValidator::isStmtRef(validatedTokens[1]) && !QueryTokenValidator::isEntRef(validatedTokens[1]) || !QueryTokenValidator::isEntRef(validatedTokens[2])) {
            throw SyntaxErrorException("Invalid " + predicateType + " clause arguments");
        }
        return validatedTokens;
    } else {
        throw SyntaxErrorException("Invalid " + predicateType + " clause syntax");
    }
}

// For relationships between entities and entities, i.e. Calls, CallsT
std::vector<std::string> QueryValidator::validateEntityEntityPredicate(const std::vector<std::string>& tokens) {
    const std::string& predicateType = tokens[0];

    if (isValidPredicateArgsNum(tokens, 2)) {
        std::vector<std::string> validatedTokens = getPredicateArgs(tokens, 2);
        if (!QueryTokenValidator::isEntRef(validatedTokens[1]) || !QueryTokenValidator::isEntRef(validatedTokens[2])) {
            throw SyntaxErrorException("Invalid " + predicateType + " clause arguments");
        }
        return validatedTokens;
    } else {
        throw SyntaxErrorException("Invalid " + predicateType + " clause syntax");
    }
}

std::vector<std::string> QueryValidator::validatePatternPredicate(const std::vector<std::string>& tokens) {
    if (isNotPredicate(tokens)) {
        std::vector<std::string> predicateTokens(tokens.begin() + 1, tokens.end());
        std::vector<std::string> validatedTokens = validatePatternPredicate(predicateTokens);
        validatedTokens.insert(validatedTokens.begin(), "not");
        return validatedTokens;
    }

    if (isValidPredicateArgsNum(tokens, 2)) {
        std::vector<std::string> validatedTokens = getPredicateArgs(tokens, 2);
        if (!QueryTokenValidator::isSynonym(validatedTokens[0]) || !QueryTokenValidator::isEntRef(validatedTokens[1]) || !QueryTokenValidator::isExpressionSpec(validatedTokens[2])) {
            throw SyntaxErrorException("Invalid pattern clause arguments");
        }
        validatedTokens.insert(validatedTokens.begin(), "pattern");
        return validatedTokens;
    } else if (isValidPredicateArgsNum(tokens, 3)) {
        std::vector<std::string> validatedTokens = getPredicateArgs(tokens, 3);
        if (!QueryTokenValidator::isSynonym(validatedTokens[0]) || !QueryTokenValidator::isEntRef(validatedTokens[1]) || !QueryTokenValidator::isWildcard(validatedTokens[2]) || !QueryTokenValidator::isWildcard(validatedTokens[3])) {
            throw SyntaxErrorException("Invalid pattern clause arguments");
        }
        validatedTokens.insert(validatedTokens.begin(), "pattern");
        return validatedTokens;
    } else {
        throw SyntaxErrorException("Invalid pattern clause syntax");
    }
}

std::vector<std::string> QueryValidator::validateWithPredicate(const std::vector<std::string>& tokens) {
    if (isNotPredicate(tokens)) {
        std::vector<std::string> predicateTokens(tokens.begin() + 1, tokens.end());
        std::vector<std::string> validatedTokens = validateWithPredicate(predicateTokens);
        validatedTokens.insert(validatedTokens.begin(), "not");
        return validatedTokens;
    }

    if (tokens.size() == 3 && QueryTokenValidator::isRef(tokens[0]) && tokens[1] == "=" && QueryTokenValidator::isRef(tokens[2])) {
        std::vector<std::string> validatedTokens = {"with", tokens[0], tokens[2]};
        return validatedTokens;
    }

    throw SyntaxErrorException("Invalid with clause syntax");
}

bool QueryValidator::isNotPredicate(const std::vector<std::string>& tokens) { 
    return tokens.size() >2 && tokens[0] == "not" && tokens[1] != "(";
}

// Validate that the predicate has the correct number of arguments
bool QueryValidator::isValidPredicateArgsNum(const std::vector<std::string>& tokens, int numOfArgs) {
    int expectedSize = numOfArgs * 2 + 2;
    int tokensLen = tokens.size();
    
    if (tokensLen == expectedSize && tokens[1] == "(" && tokens[tokensLen - 1] == ")") {
        for (int i = 0; i < numOfArgs - 1; i++) {
            if (tokens[2*i+3] != ",") {
                return false;
            }
        }
        return true;
    }

    return false;
}

// Extract the arguments from a predicate
std::vector<std::string> QueryValidator::getPredicateArgs(const std::vector<std::string>& tokens, int numOfArgs) {
    std::vector<std::string> results = { tokens[0] };

    for (int i = 0; i < numOfArgs; i++) {
        results.push_back(tokens[2*i+2]);
    }

    return results;
}