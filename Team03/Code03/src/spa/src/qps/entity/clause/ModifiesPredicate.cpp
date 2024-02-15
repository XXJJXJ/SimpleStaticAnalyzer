#include "ModifiesPredicate.h"
#include <stdexcept>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


ModifiesPredicate::ModifiesPredicate(ModifiesLhsRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) { // Explicit initialization
    // After initializing, you can perform further checks or logic as needed
    if (!isValidLhs(this->lhs) || !isValidRhs(this->rhs)) {
        throw std::invalid_argument("Invalid arguments for ModifiesPredicate constructor");
    }
}

std::shared_ptr<Strategy> ModifiesPredicate::getStrategy() const {
    // Placeholder logic for strategy selection
    return nullptr;
}

bool ModifiesPredicate::isValidLhs(const ModifiesLhsRef& lhs) {
    return std::visit(overloaded {
            [](const int&) { return true; }, // int is always valid for StatementRef
            [](const Synonym& syn) {
                // Check if Synonym is of type stmt or procedure
                return syn.getType() == EntityType::Stmt || syn.getType() == EntityType::Procedure;
            },
            [](const std::string& str) { return str == "_"; }, // "_" is valid
            [](const auto&) { return false; } // Fallback for EntityRef (procedure names, variable names)
    }, lhs);
}


bool ModifiesPredicate::isValidRhs(const EntityRef& rhs) {
    // EntityRef can be a Synonym of type variable or a variable name (string), or "_"
    return std::visit(overloaded {
            [](const Synonym& syn) {
                // Check if Synonym is of type variable
                return syn.getType() == EntityType::Variable;
            },
            [](const std::string& str) { return !str.empty(); }, // Any non-empty string is valid
    }, rhs);
}

