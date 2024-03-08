#include "PredicateUtils.h"
#include "qps/QueryValidator.h"

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

bool isValidEntityRef(const EntityRef& ref) { 
    QueryValidator qv;
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return VALID_DESIGN_ENTITY_TYPES.find(synonym.getType()) != VALID_DESIGN_ENTITY_TYPES.end();
    } else if (std::holds_alternative<std::string>(ref)) {
        std::string refString = std::get<std::string>(ref);
        return refString == WILDCARD || qv.isIdent(refString); 
    } 
    return false;
}

bool isValidProcAndStmtRef(const ProcAndStmtRef& ref) {
    QueryValidator qv;
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return VALID_STATEMENT_TYPES.find(synonym.getType()) != VALID_STATEMENT_TYPES.end() ||
               VALID_PROCEDURE_TYPES.find(synonym.getType()) != VALID_PROCEDURE_TYPES.end();
    } else if (std::holds_alternative<std::string>(ref)) {
        std::string refString = std::get<std::string>(ref);
        return refString != WILDCARD && qv.isIdent(refString);
    } else if (std::holds_alternative<int>(ref)) {
        // Assuming int is always a valid statement reference
        return std::get<int>(ref) > 0;
    }
    return false;
}


bool isValidVariable(const EntityRef& ref) {
    QueryValidator qv;
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return synonym.getType() == EntityType::Variable;
    } else if (std::holds_alternative<std::string>(ref)) {
        std::string refString = std::get<std::string>(ref);
        return refString == WILDCARD || qv.isIdent(refString);
    }

    return false;
}

bool isWildcard(StatementRef& ref) {
    return std::holds_alternative<std::string>(ref) && std::get<std::string>(ref) != WILDCARD;
}

bool isWildcard(EntityRef & ref) {
    return std::holds_alternative<std::string>(ref) && std::get<std::string>(ref) != WILDCARD;
}

bool hasWildcard(std::string& expr) {
    // if both first and last are "_", then it's a wildcard
    return (expr.size() > 1 && expr[0] == '_' && expr[expr.size() - 1] == '_') || expr == "_";
}

std::string stripWildcard(std::string& expr) {
    if (expr == "_") {
        return "";
    }
    if (hasWildcard(expr)) {
        // Remove _" and "_
        return expr.substr(2, expr.size() - 4);
    }
    return expr;
}

std::shared_ptr<ColumnValidator> getValidatorForStatementRef(const StatementRef& stmtRef) {
    return std::visit([](auto&& arg) -> std::shared_ptr<ColumnValidator> {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            return std::make_shared<StatementNumberValidator>(arg);
        } else if constexpr (std::is_same_v<T, Synonym>) {
            return std::make_shared<SynonymValidator>(arg);
        } else if constexpr (std::is_same_v<T, std::string>) {
            if (arg == "_") {
                return std::make_shared<WildcardValidator>();
            }
        }
        // Fallback for unrecognized types
        throw QPSEvaluationException("Unsupported StatementRef type for validator creation.");
    }, stmtRef);
}

std::shared_ptr<ColumnValidator> getValidatorForEntityRef(const EntityRef& entRef) {
    return std::visit([](auto&& arg) -> std::shared_ptr<ColumnValidator> {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Synonym>) {
            return std::make_shared<SynonymValidator>(arg);
        } else if constexpr (std::is_same_v<T, std::string>) {
            if (arg == "_") {
                return std::make_shared<WildcardValidator>();
            } else {
                return std::make_shared<IdentifierValidator>(arg);
            }
        }
        // Fallback for unrecognized types
        throw std::invalid_argument("Unsupported EntityRef type for validator creation.");
    }, entRef);
}

std::shared_ptr<ColumnValidator> getValidatorForProcAndStmtRef(const ProcAndStmtRef& procAndStmtRef) {
    return std::visit([&](auto&& arg) -> std::shared_ptr<ColumnValidator> {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            // Directly treat as StatementRef and fetch its validator
            return getValidatorForStatementRef(arg);
        } else {
            // Convert to EntityRef and fetch its validator
            EntityRef entRef = arg; // Implicitly casts Synonym or std::string to EntityRef
            return getValidatorForEntityRef(entRef);
        }
    }, procAndStmtRef);
}

