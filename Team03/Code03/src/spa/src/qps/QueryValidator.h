#ifndef SPA_QUERYVALIDATOR_H
#define SPA_QUERYVALIDATOR_H
#include <string>
#include <vector>
#include "qps/entity/clause/PredicateUtils.h"

class QueryValidator {
public:
    QueryValidator();
    ~QueryValidator();

    static std::vector<std::vector<std::vector<std::string>>> validate(const std::vector<std::string> &tokens);
    static std::vector<std::vector<std::vector<std::string>>> splitTokens(const std::vector<std::string> &tokens);
    static std::vector<std::string> validateDeclaration(const std::vector<std::string> &tokens);
    static std::vector<std::string> validateSelection(const std::vector<std::string> &tokens);
    static std::vector<std::string> validatePredicate(const std::vector<std::string> &tokens, ClauseType &prevClause);
    static std::vector<std::string> validateSuchThatPredicate(const std::vector<std::string> &tokens);
    static std::vector<std::string> validateStatementStatementPredicate(const std::vector<std::string> &tokens);
    static std::vector<std::string> validateStmtEntEntityPredicate(const std::vector<std::string> &tokens);
    static std::vector<std::string> validateEntityEntityPredicate(const std::vector<std::string> &tokens);
    static std::vector<std::string> validatePatternPredicate(const std::vector<std::string> &tokens);
    static std::vector<std::string> validateWithPredicate(const std::vector<std::string> &tokens);
    static ClauseType getClauseType(const std::vector<std::string> &tokens);
    static bool isNotPredicate(const std::vector<std::string> &tokens);
    static bool isValidPredicateArgsNum(const std::vector<std::string> &tokens, int numOfArgs);
    static std::vector<std::string> getPredicateArgs(const std::vector<std::string> &tokens, int numOfArgs);
};

#endif // SPA_QUERYVALIDATOR_H