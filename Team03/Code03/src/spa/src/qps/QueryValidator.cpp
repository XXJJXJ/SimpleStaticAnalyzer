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

    for (std::vector<std::string>& predicate : predicateTokens) {
        validatedPredicateTokens.push_back(validatePredicate(predicate));
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
std::vector<std::string> QueryValidator::validatePredicate(const std::vector<std::string>& tokens) {
    if (tokens.size() > 3 && tokens[0] == "such" && tokens[1] == "that") {
        PredicateType predicateType = getPredicateType(tokens[2]);
        std::vector<std::string> predicateTokens(tokens.begin() + 2, tokens.end());
        switch (predicateType) {
            case PredicateType::Follows:
            case PredicateType::FollowsT:
            case PredicateType::Parent:
            case PredicateType::ParentT:
                return validateStatementStatementPredicate(predicateTokens);
            case PredicateType::Modifies:
            case PredicateType::Uses:
                return validateStmtEntEntityPredicate(predicateTokens);
            case PredicateType::Pattern:
            case PredicateType::Invalid:
                throw SyntaxErrorException("Invalid such that clause keyword " + tokens[2]);
        }
    } else if (tokens.size() > 2 && getPredicateType(tokens[0]) == PredicateType::Pattern) {
        return validateAssignPatternPredicate(tokens);
    } else {
        throw SyntaxErrorException("Invalid clause keyword");
    }
}

// TODO: add another layer of abstraction for the 3 functions below
// TODO: get rid of magic numbers

// For relationships between statements, i.e. Follows, FollowsT, Parent, ParentT
std::vector<std::string> QueryValidator::validateStatementStatementPredicate(const std::vector<std::string>& tokens) {
    std::vector<std::string> validatedTokens;
    const std::string& predicateType = tokens[0];
    validatedTokens.push_back(predicateType);
    if (tokens.size() == 6 && tokens[1] == "(" && tokens[3] == "," && tokens[5] == ")") {
        const std::string& lhs = tokens[2];
        const std::string& rhs = tokens[4];
        if (!isStmtRef(lhs) || !isStmtRef(rhs)) {
            throw SyntaxErrorException("Invalid " + predicateType + " clause arguments");
        }
        validatedTokens.push_back(lhs);
        validatedTokens.push_back(rhs);
    } else {
        throw SyntaxErrorException("Invalid " + predicateType + " clause syntax");
    }

    return validatedTokens;
}

// For relationships between statements/entities and entities, i.e. Modifies, Uses
std::vector<std::string> QueryValidator::validateStmtEntEntityPredicate(const std::vector<std::string>& tokens) {
    std::vector<std::string> validatedTokens;
    const std::string& predicateType = tokens[0];
    validatedTokens.push_back(predicateType);
    if (tokens.size() == 6 && tokens[1] == "(" && tokens[3] == "," && tokens[5] == ")") {
        const std::string& lhs = tokens[2];
        const std::string& rhs = tokens[4];
        if (!isStmtRef(lhs) && !isEntRef(lhs) || !isEntRef(rhs)) {
            throw SyntaxErrorException("Invalid " + predicateType + " clause arguments");
        }
        validatedTokens.push_back(lhs);
        validatedTokens.push_back(rhs);
    } else {
        throw SyntaxErrorException("Invalid " + predicateType + " clause syntax");
    }

    return validatedTokens;
}

std::vector<std::string> QueryValidator::validateAssignPatternPredicate(const std::vector<std::string>& tokens) {
    std::vector<std::string> validatedTokens;
    validatedTokens.push_back(tokens[0]);

    if (tokens.size() == 7 && tokens[2] == "(" && tokens[4] == "," && tokens[6] == ")") {
        const std::string& assignSyn = tokens[1];
        const std::string& lhs = tokens[3];
        const std::string& rhs = tokens[5];

        if (!isSynonym(assignSyn) || !isEntRef(lhs) || !isExpressionSpec(rhs)) {
            throw SyntaxErrorException("Invalid pattern clause arguments");
        }
        validatedTokens.push_back(assignSyn);
        validatedTokens.push_back(lhs);
        validatedTokens.push_back(rhs);
    } else {
        throw SyntaxErrorException("Invalid pattern clause syntax");
    }

    return validatedTokens;
}


// ai-gen start(copilot, 2, e)

// Check if token is a single letter
bool QueryValidator::isLetter(std::string const& token) {
    return token.length() == 1 && std::isalpha(token[0]);
}

// Check if token is a single digit from 0-9
bool QueryValidator::isDigit(std::string const& token) {
    return token.length() == 1 && isdigit(token[0]);
}

// Check if token is a single non-zero digit from 1-9
bool QueryValidator::isNzDigit(std::string const& token) {
    return isDigit(token) && token[0] >= '1';
}

// Check if token is a number (can be multiple digits)
// Definition of integer: 0 | NZDIGIT ( DIGIT )* - no leading zero
bool QueryValidator::isInteger(std::string const& token) {
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
bool QueryValidator::isIdent(std::string const& token) {

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
bool QueryValidator::isName(std::string const& token) { return isIdent(token); }

// Check if token is a valid synonym
// Definition of synonym: IDENT
bool QueryValidator::isSynonym(std::string const& token) { return isIdent(token); }

bool QueryValidator::isWildcard(std::string const& token) {
    return token == "_";
}

// Check if token is a valid statement reference
// Definition of stmtRef: synonym | '_' | INTEGER
bool QueryValidator::isStmtRef(std::string const& token) {
    return isSynonym(token) || isWildcard(token) || isInteger(token);
}

// Check if token is a valid entity reference
// Definition of entRef: synonym | '_' | '"' IDENT '"'
bool QueryValidator::isEntRef(std::string const& token) {
    return isSynonym(token) || isWildcard(token) ||
           (token.length() > 2 && token.front() == '"' && token.back() == '"' &&
            isIdent(token.substr(1, token.length() - 2)));
}

// Definition of expressionSpec :  '"' expr'"' | '_' '"' expr '"' '_' | '_'
bool QueryValidator::isExpressionSpec(std::string const& token) {
    size_t len = token.length();
    return (len > 2 && token[0] == '"' && token[len - 1] == '"' && isExpr(token.substr(1, len-2)))||
           (len > 4 && token[0] == '_' && token[1] == '"' && token[len - 2] == '"' && token[len - 1] == '_' && isExpr(token.substr(2, len-4)))||
           isWildcard(token);
}

bool QueryValidator::isExpr(std::string input) {
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '+' || input[i] == '-') {
            if (isExpr(input.substr(0, i)) && isTerm(input.substr(i + 1))) {
                return true;
            }
        }
    }

    return isTerm(input);
}

bool QueryValidator::isTerm(const std::string& input) {
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == '*' || input[i] == '/' || input[i] == '%') {
            if (isTerm(input.substr(0, i)) && isFactor(input.substr(i + 1))) {
                return true;
            }
        }
    }
    return isFactor(input);
}

bool QueryValidator::isFactor(const std::string& input) {
    if (input.size() >= 2 && input.front() == '(' && input.back() == ')') {
        return isExpr(input.substr(1, input.size() - 2));
    } else {
        return isName(input) || isInteger(input);
    }
}

// ai-gen end