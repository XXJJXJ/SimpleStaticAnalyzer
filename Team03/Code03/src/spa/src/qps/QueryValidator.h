/*
 * Created by ZHENGTAO JIANG on 8/2/24.
 *
 * Methods for validating input string based on the predefined PQL grammar
 * Returns true if valid, false if invalid
 *
 */

#ifndef SPA_QUERYVALIDATOR_H
#define SPA_QUERYVALIDATOR_H
#include <string>

class QueryValidator {
  public:
    QueryValidator();
    ~QueryValidator();

    static bool isLetter(const std::string& token);
    static bool isDigit(const std::string& token);
    static bool isNzDigit(const std::string& token);
    static bool isInteger(const std::string& token);
    static bool isIdent(const std::string& token);
    static bool isName(const std::string& token);
    static bool isSynonym(const std::string& token);
    bool isStmtRef(const std::string& token);
    bool isEntRef(const std::string& token);
};

#endif // SPA_QUERYVALIDATOR_H