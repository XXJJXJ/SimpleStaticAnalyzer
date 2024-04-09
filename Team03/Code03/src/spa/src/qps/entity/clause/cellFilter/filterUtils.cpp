#include "filterUtils.h"

std::shared_ptr<CellFilter> getFilterForStatementRef(const StatementRef& stmtRef) {
    return std::visit([](auto&& arg) -> std::shared_ptr<CellFilter> {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            return std::make_shared<StatementNumberFilter>(arg);
        } else if constexpr (std::is_same_v<T, Synonym>) {
            return std::make_shared<SynonymFilter>(arg);
        } else if constexpr (std::is_same_v<T, std::string>) {
            if (arg == "_") {
                return std::make_shared<WildcardFilter>();
            }
        }
        // Fallback for unrecognized types
        throw QPSEvaluationException("Unsupported StatementRef type for cellFilter creation.");
    }, stmtRef);
}

std::shared_ptr<CellFilter> getFilterForRef(const Ref& ref) {
    // If ref contains synonym, return synonym filter
    if (ref.holdsSynonym()) {
        return std::make_shared<SynonymFilter>(*ref.getSynonym());
    }

    // Otherwise, code shouldn't reach here, as non-synonym ref shouldn't correspond to any column
    throw QPSEvaluationException("filterUtils::getFilterForRef Unsupported Ref type for cellFilter creation.");
}

std::shared_ptr<CellFilter> getFilterForEntityRef(const EntityRef& entRef) {
    return std::visit([](auto&& arg) -> std::shared_ptr<CellFilter> {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Synonym>) {
            return std::make_shared<SynonymFilter>(arg);
        } else if constexpr (std::is_same_v<T, std::string>) {
            if (arg == "_") {
                return std::make_shared<WildcardFilter>();
            } else {
                return std::make_shared<IdentifierFilter>(arg);
            }
        }
        // Fallback for unrecognized types
        throw std::invalid_argument("Unsupported EntityRef type for cellFilter creation.");
    }, entRef);
}

std::shared_ptr<CellFilter> getFilterForProcAndStmtRef(const ProcAndStmtRef& procAndStmtRef) {
    return std::visit([&](auto&& arg) -> std::shared_ptr<CellFilter> {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            // Directly treat as StatementRef and fetch its cell filter
            return getFilterForStatementRef(arg);
        } else {
            // Convert to EntityRef and fetch its cell filter
            EntityRef entRef = arg; // Implicitly casts Synonym or std::string to EntityRef
            return getFilterForEntityRef(entRef);
        }
    }, procAndStmtRef);
}