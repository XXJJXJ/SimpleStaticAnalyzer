/*
 * Created by ZHENGTAO JIANG on 8/2/24.
 *
 * Methods for validating input string based on the predefined PQL grammar
 *
 */

#ifndef SPA_QUERYVALIDATOR_H
#define SPA_QUERYVALIDATOR_H
#include <string>
#include <vector>

class QueryValidator {
public:
    QueryValidator();
    ~QueryValidator();

    static std::vector<std::vector<std::vector<std::string>>> validate(const std::vector<std::vector<std::vector<std::string>>>& tokens);
    static bool isLetter(const std::string& token);
    static bool isDigit(const std::string& token);
    static bool isNzDigit(const std::string& token);
    static bool isInteger(const std::string& token);
    static bool isIdent(const std::string& token);
    static bool isName(const std::string& token);
    static bool isSynonym(const std::string& token);
    static bool isWildcard(const std::string& token);
    static bool isStmtRef(const std::string& token);
    static bool isEntRef(const std::string& token);
    static bool isExpressionSpec(const std::string& token);
    static bool isExpr(std::string token);
    static bool isTerm(const std::string& token);
    static bool isFactor(const std::string& token);
    static std::vector<std::string> validateDeclaration(const std::vector<std::string>& tokens);
    static std::vector<std::string> validateSelection(const std::vector<std::string>& tokens);
    static std::vector<std::string> validatePredicate(const std::vector<std::string>& tokens);
    static std::vector<std::string> validateStatementStatementPredicate(const std::vector<std::string>& tokens);
    static std::vector<std::string> validateStmtEntEntityPredicate(const std::vector<std::string>& tokens);
    static std::vector<std::string> validateEntityEntityPredicate(const std::vector<std::string>& tokens);
    static std::vector<std::string> validateAssignPatternPredicate(const std::vector<std::string>& tokens);
};

#endif // SPA_QUERYVALIDATOR_H