// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "UsesPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

UsesPredicate::UsesPredicate(UsesLhsRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidLhs(this->lhs) || !isValidRhs(this->rhs)) {
        throw SyntaxErrorException("Invalid arguments for UsesPredicate constructor");
    }
}

std::shared_ptr<Strategy> UsesPredicate::getStrategy() const {
    // Placeholder logic for strategy selection
    return nullptr;
}

bool UsesPredicate::isValidLhs(const UsesLhsRef& lhs) {
    return std::visit(overloaded {
            [](const int&) { return true; },
            [](const Synonym& syn) { return syn.getType() == EntityType::Stmt || syn.getType() == EntityType::Procedure; },
            [](const std::string& str) { return !str.empty(); },
            [](const auto&) { return false; }
    }, lhs);
}

bool UsesPredicate::isValidRhs(const EntityRef& rhs) {
    return std::visit(overloaded {
            [](const Synonym& syn) { return syn.getType() == EntityType::Variable; },
            [](const std::string& str) { return !str.empty(); }
    }, rhs);
}


// ai-gen end