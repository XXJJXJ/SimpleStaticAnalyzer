/*
 * Created by ZHENGTAO JIANG on 8/2/24.
 */

#include "QueryValidator.h"
#include "QueryParser.h"
#include <algorithm>

QueryValidator::QueryValidator() {}
QueryValidator::~QueryValidator() {}

// ai-gen start(copilot, 2, e)

// Check if token is a single letter
bool QueryValidator::isLetter(std::string const& token) {
    return token.length() == 1 && std::isalpha(token[0]);
}

// Check if token is a single digit from 0-9
bool QueryValidator::isDigit(std::string const& token) {
    return token.length() == 1 && token[0] >= '0' && token[0] <= '9';
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
        if (!isalpha(token[0]) && !isDigit(token.substr(i, 1))) {
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
// Types of synonyms (Defined in EntityType.h). Unknown is not a valid synonym
bool QueryValidator::isSynonym(std::string const& token) {
    return token == "stmt" || token == "read" || token == "print" || token == "call" ||
           token == "while" || token == "if" || token == "assign" || token == "variable" ||
           token == "constant" || token == "procedure";
}

// Check if token is a valid statement reference
// Definition of stmtRef: synonym | '_' | INTEGER
bool QueryValidator::isStmtRef(std::string const& token) {
    return isSynonym(token) || token == "_" || isInteger(token);
}

// Check if token is a valid entity reference
// Definition of entRef: synonym | '_' | '"' IDENT '"'
bool QueryValidator::isEntRef(std::string const& token) {
    return isSynonym(token) || token == "_" ||
           (token.length() > 2 && token.front() == '"' && token.back() == '"' &&
            isIdent(token.substr(1, token.length() - 2)));
}

// ai-gen end