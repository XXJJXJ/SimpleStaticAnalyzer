#include "PredicateUtils.h"

bool isValidStatementRef(const StatementRef &ref) {
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return VALID_STATEMENT_TYPES.find(synonym.getType()) != VALID_STATEMENT_TYPES.end();
    } else if (std::holds_alternative<std::string>(ref)) {
        return std::get<std::string>(ref) == WILDCARD;
    } else if (std::holds_alternative<int>(ref)) {
        // Assuming int is always a valid statement reference
        return std::get<int>(ref) > 0;
    }
    return false;
}

bool isWildcard(StatementRef& ref) {
    return std::holds_alternative<std::string>(ref) && std::get<std::string>(ref) != WILDCARD;
}

bool isWildcard(EntityRef & ref) {
    return std::holds_alternative<std::string>(ref) && std::get<std::string>(ref) != WILDCARD;
}