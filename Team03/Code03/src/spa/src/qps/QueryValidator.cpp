/*
 * Created by ZHENGTAO JIANG on 8/2/24.
 */

#include "QueryValidator.h"
#include <algorithm>
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/EntityType.h"
#include "qps/util/EntityTypeConverter.h"
#include "qps/entity/clause/PredicateUtils.h"


QueryValidator::QueryValidator() = default;
QueryValidator::~QueryValidator() = default;

// Takes in tokens, validates them for syntax errors, then returns a simplified list of tokens (without unnecessary punctuation marks etc.) to be parsed by QueryParser
std::vector<std::vector<std::vector<std::string>>> QueryValidator::validate(const std::vector<std::vector<std::vector<std::string>>>& tokens) {
    std::vector<std::vector<std::vector<std::string>>> validatedQuery;

    std::vector<std::vector<std::string>> declarationsTokens = tokens[0];
    std::vector<std::vector<std::string>> selectionsTokens = tokens[1];
    std::vector<std::vector<std::string>> predicateTokens = tokens[2];

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

            if (!isName(name)) { // Validate synonym name more rigorously
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
                if (!isName(token)) {
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
        if (!isName(token)) {
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
    } case ClauseType::And: {
        std::vector<std::string> predicateTokens(tokens.begin() + 1, tokens.end());
        switch (prevClause) {
        case ClauseType::SuchThat:
            return validateSuchThatPredicate(predicateTokens);
        case ClauseType::Pattern:
            return validatePatternPredicate(predicateTokens);
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
    } else if (tokens.size() > 2 && tokens[0] == "and") {
        return ClauseType::And;
    } else {
        return ClauseType::Invalid;
    }
}

std::vector<std::string> QueryValidator::validateSuchThatPredicate(const std::vector<std::string>& tokens) {
    PredicateType predicateType = getPredicateType(tokens[0]);
    switch (predicateType) {
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
    case PredicateType::Pattern:
    case PredicateType::Invalid:
        throw SyntaxErrorException("Invalid such that clause keyword " + tokens[0]);
    }
}

// For relationships between statements, i.e. Follows, FollowsT, Parent, ParentT
std::vector<std::string> QueryValidator::validateStatementStatementPredicate(const std::vector<std::string>& tokens) {
    const std::string& predicateType = tokens[0];

    if (isValidPredicateArgsNum(tokens, 2)) {
        std::vector<std::string> validatedTokens = getPredicateArgs(tokens, 2);
        if (!isStmtRef(validatedTokens[1]) || !isStmtRef(validatedTokens[2])) {
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
        if (!isStmtRef(validatedTokens[1]) && !isEntRef(validatedTokens[1]) || !isEntRef(validatedTokens[2])) {
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
        if (!isEntRef(validatedTokens[1]) || !isEntRef(validatedTokens[2])) {
            throw SyntaxErrorException("Invalid " + predicateType + " clause arguments");
        }
        return validatedTokens;
    } else {
        throw SyntaxErrorException("Invalid " + predicateType + " clause syntax");
    }
}

std::vector<std::string> QueryValidator::validatePatternPredicate(const std::vector<std::string>& tokens) {
    if (isValidPredicateArgsNum(tokens, 2)) {
        std::vector<std::string> validatedTokens = getPredicateArgs(tokens, 2);
        if (!isSynonym(validatedTokens[0]) || !isEntRef(validatedTokens[1]) || !isExpressionSpec(validatedTokens[2])) {
            throw SyntaxErrorException("Invalid pattern clause arguments");
        }
        validatedTokens.insert(validatedTokens.begin(), "pattern");
        return validatedTokens;
    } else if (isValidPredicateArgsNum(tokens, 3)) {
        std::vector<std::string> validatedTokens = getPredicateArgs(tokens, 3);
        if (!isSynonym(validatedTokens[0]) || !isEntRef(validatedTokens[1]) || !isWildcard(validatedTokens[2]) || !isWildcard(validatedTokens[3])) {
            throw SyntaxErrorException("Invalid pattern clause arguments");
        }
        validatedTokens.insert(validatedTokens.begin(), "pattern");
        return validatedTokens;
    } else {
        throw SyntaxErrorException("Invalid pattern clause syntax");
    }
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

// ai-gen start(copilot, 2, e)

// Check if token is a single letter
bool QueryValidator::isLetter(const std::string& token) {
    return token.length() == 1 && std::isalpha(token[0]);
}

// Check if token is a single digit from 0-9
bool QueryValidator::isDigit(const std::string& token) {
    return token.length() == 1 && isdigit(token[0]);
}

// Check if token is a single non-zero digit from 1-9
bool QueryValidator::isNzDigit(const std::string& token) {
    return isDigit(token) && token[0] >= '1';
}

// Check if token is a number (can be multiple digits)
// Definition of integer: 0 | NZDIGIT ( DIGIT )* - no leading zero
bool QueryValidator::isInteger(const std::string& token) {
    if (token.empty()) {
        return false;
    }

    // If single digit, check if it is digit
    if (token.length() == 1) {
        return isDigit(token);
    }

    // If multiple digits, check if first digit is non-zero and rest are digits
    return isNzDigit(token.substr(0, 1)) && std::all_of(token.begin() + 1, token.end(), ::isdigit);
}

// Check if token is a valid identifier
// Definition of identifier: LETTER ( LETTER | DIGIT )*
bool QueryValidator::isIdent(const std::string& token) {

    if (token.empty()) {
        return false;
    }

    // Check if first character is a letter
    if (!isLetter(token.substr(0, 1))) {
        return false;
    }

    // Check if rest of the characters are letters or digits
    for (size_t i = 1; i < token.length(); i++) {
        if (!isalnum(token[i])) {
            return false;
        }
    }

    // Token is not empty, starts with letter, and rest are letters or digits
    return true;
}

// Check if token is a valid name
// Definition of name: LETTER ( LETTER | DIGIT )*
bool QueryValidator::isName(const std::string& token) { return isIdent(token); }

// Check if token is a valid synonym
// Definition of synonym: IDENT
bool QueryValidator::isSynonym(const std::string& token) { return isIdent(token); }

bool QueryValidator::isWildcard(const std::string& token) {
    return token == "_";
}

// Check if token is a valid statement reference
// Definition of stmtRef: synonym | '_' | INTEGER
bool QueryValidator::isStmtRef(const std::string& token) {
    return isSynonym(token) || isWildcard(token) || isInteger(token);
}

// Check if token is a valid entity reference
// Definition of entRef: synonym | '_' | '"' IDENT '"'
bool QueryValidator::isEntRef(const std::string& token) {
    return isSynonym(token) || isWildcard(token) ||
           (token.length() > 2 && token.front() == '"' && token.back() == '"' &&
            isIdent(token.substr(1, token.length() - 2)));
}

// Definition of expressionSpec :  '"' expr'"' | '_' '"' expr '"' '_' | '_'
bool QueryValidator::isExpressionSpec(const std::string& token) {
    size_t len = token.length();
    return (len > 2 && token[0] == '"' && token[len - 1] == '"' && isExpr(token.substr(1, len-2)))||
           (len > 4 && token[0] == '_' && token[1] == '"' && token[len - 2] == '"' && token[len - 1] == '_' && isExpr(token.substr(2, len-4)))||
           isWildcard(token);
}

bool QueryValidator::isExpr(std::string token) {
    token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
    for (size_t i = 0; i < token.size(); ++i) {
        if (token[i] == '+' || token[i] == '-') {
            if (isExpr(token.substr(0, i)) && isTerm(token.substr(i + 1))) {
                return true;
            }
        }
    }

    return isTerm(token);
}

bool QueryValidator::isTerm(const std::string& token) {
    for (size_t i = 0; i < token.size(); i++) {
        if (token[i] == '*' || token[i] == '/' || token[i] == '%') {
            if (isTerm(token.substr(0, i)) && isFactor(token.substr(i + 1))) {
                return true;
            }
        }
    }
    return isFactor(token);
}

bool QueryValidator::isFactor(const std::string& token) {
    if (token.size() >= 2 && token.front() == '(' && token.back() == ')') {
        return isExpr(token.substr(1, token.size() - 2));
    } else {
        return isName(token) || isInteger(token);
    }
}

// ai-gen end