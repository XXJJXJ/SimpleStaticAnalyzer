#include "QueryTokenValidator.h"
#include "qps/entity/clause/PredicateUtils.h"

// ai-gen start(copilot, 2, e)

// Check if token is a single letter
bool QueryTokenValidator::isLetter(const std::string &token) {
    return token.length() == 1 && std::isalpha(token[0]);
}

// Check if token is a single digit from 0-9
bool QueryTokenValidator::isDigit(const std::string &token) {
    return token.length() == 1 && isdigit(token[0]);
}

// Check if token is a single non-zero digit from 1-9
bool QueryTokenValidator::isNzDigit(const std::string &token) {
    return isDigit(token) && token[0] >= '1';
}

// Check if token is a number (can be multiple digits)
// Definition of integer: 0 | NZDIGIT ( DIGIT )* - no leading zero
bool QueryTokenValidator::isInteger(const std::string &token) {
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
bool QueryTokenValidator::isIdent(const std::string &token) {

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
bool QueryTokenValidator::isName(const std::string &token) { return isIdent(token); }

// Check if token is a valid synonym
// Definition of synonym: IDENT
bool QueryTokenValidator::isSynonym(const std::string &token) { return isIdent(token); }

bool QueryTokenValidator::isWildcard(const std::string &token) {
    return token == "_";
}

// Check if token is a valid statement reference
// Definition of stmtRef: synonym | '_' | INTEGER
bool QueryTokenValidator::isStmtRef(const std::string &token) {
    return isSynonym(token) || isWildcard(token) || isInteger(token);
}

// Check if token is a valid entity reference
// Definition of entRef: synonym | '_' | '"' IDENT '"'
bool QueryTokenValidator::isEntRef(const std::string &token) {
    return isSynonym(token) || isWildcard(token) ||
        (token.length() > 2 && token.front() == '"' && token.back() == '"' &&
            isIdent(token.substr(1, token.length() - 2)));
}

// Definition of expressionSpec :  '"' expr'"' | '_' '"' expr '"' '_' | '_'
bool QueryTokenValidator::isExpressionSpec(const std::string &token) {
    size_t len = token.length();
    return (len > 2 && token[0] == '"' && token[len - 1] == '"' && isExpr(token.substr(1, len - 2))) ||
        (len > 4 && token[0] == '_' && token[1] == '"' && token[len - 2] == '"' && token[len - 1] == '_'
            && isExpr(token.substr(2, len - 4))) ||
        isWildcard(token);
}

bool QueryTokenValidator::isExpr(std::string token) {
    for (size_t i = 0; i < token.size(); ++i) {
        if (token[i] == '+' || token[i] == '-') {
            if (isExpr(token.substr(0, i)) && isTerm(token.substr(i + 1))) {
                return true;
            }
        }
    }

    return isTerm(token);
}

bool QueryTokenValidator::isTerm(const std::string &token) {
    for (size_t i = 0; i < token.size(); i++) {
        if (token[i] == '*' || token[i] == '/' || token[i] == '%') {
            if (isTerm(token.substr(0, i)) && isFactor(token.substr(i + 1))) {
                return true;
            }
        }
    }
    return isFactor(token);
}

bool QueryTokenValidator::isFactor(const std::string &token) {
    if (token.size() >= 2 && token.front() == '(' && token.back() == ')') {
        return isExpr(token.substr(1, token.size() - 2));
    } else {
        return isName(token) || isInteger(token);
    }
}

// ai-gen end

bool QueryTokenValidator::isAttrRef(const std::string &token) {
    size_t pos = token.find('.');
    if (pos != std::string::npos) {
        return isSynonym(token.substr(0, pos)) && isAttrName(token.substr(pos + 1));
    }
    return false;
}

bool QueryTokenValidator::isAttrName(const std::string &token) {
    AttributeType attributeType = getAttributeTypeFromString(token);
    return attributeType != AttributeType::Invalid;
}

bool QueryTokenValidator::isRef(const std::string &token) {
    return isInteger(token) || isAttrRef(token) ||
        (token.length() > 2 && token.front() == '"' && token.back() == '"' &&
            isIdent(token.substr(1, token.length() - 2)));
}
