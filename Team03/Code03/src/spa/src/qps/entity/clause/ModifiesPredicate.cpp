// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "ModifiesPredicate.h"
#include <stdexcept> // For std::invalid_argument

ModifiesPredicate::ModifiesPredicate(ModifiesLhsRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidLhs(this->lhs) || !isValidRhs(this->rhs)) {
        throw std::invalid_argument("Invalid arguments for ModifiesPredicate constructor");
    }
}

std::shared_ptr<Strategy> ModifiesPredicate::getStrategy() const {
    // Placeholder logic for strategy selection
    return nullptr; // Return a valid shared_ptr to a Strategy object as needed
}

bool ModifiesPredicate::isValidLhs(const ModifiesLhsRef& lhs) {
    return std::visit(overloaded {
            [](const int&) { return true; },
            [](const Synonym& syn) { return syn.getType() == EntityType::Stmt || syn.getType() == EntityType::Procedure; },
            [](const std::string& str) { return !str.empty(); },
            [](const auto&) { return false; } // No longer needed, but kept for completeness
    }, lhs);
}

bool ModifiesPredicate::isValidRhs(const EntityRef& rhs) {
    return std::visit(overloaded {
            [](const Synonym& syn) { return syn.getType() == EntityType::Variable; },
            [](const std::string& str) { return !str.empty(); }
    }, rhs);
}


// ai-gen end