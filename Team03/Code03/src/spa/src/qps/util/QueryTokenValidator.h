#ifndef SPA_QUERYTOKENVALIDATOR_H
#define SPA_QUERYTOKENVALIDATOR_H

#include <string>

class QueryTokenValidator {
public:
    static bool isLetter(const std::string &token);
    static bool isDigit(const std::string &token);
    static bool isNzDigit(const std::string &token);
    static bool isInteger(const std::string &token);
    static bool isIdent(const std::string &token);
    static bool isName(const std::string &token);
    static bool isSynonym(const std::string &token);
    static bool isWildcard(const std::string &token);
    static bool isStmtRef(const std::string &token);
    static bool isEntRef(const std::string &token);
    static bool isExpressionSpec(const std::string &token);
    static bool isExpr(std::string token);
    static bool isTerm(const std::string &token);
    static bool isFactor(const std::string &token);
    static bool isAttrRef(const std::string &token);
    static bool isAttrName(const std::string &token);
    static bool isRef(const std::string &token);
};

#endif //SPA_QUERYTOKENVALIDATOR_H
