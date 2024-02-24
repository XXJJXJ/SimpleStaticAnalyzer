// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsTPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

FollowsTPredicate::FollowsTPredicate(StatementRef lhs, StatementRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidStmtRef(this->lhs) || !isValidStmtRef(this->rhs)) {
        throw SyntaxErrorException("Invalid arguments for FollowsTPredicate constructor");
    }
}

std::shared_ptr<Strategy> FollowsTPredicate::getStrategy() const {
    // Placeholder logic for strategy selection specific to Follows*
    return nullptr; // Return a valid shared_ptr to a Strategy object as needed
}

bool FollowsTPredicate::isValidStmtRef(const StatementRef& ref) {
    // Implement validation logic for statement references
    return std::visit(overloaded {
            [](const int&) { return true; }, // int is always valid for StatementRef
            [](const Synonym& syn) {
                // Check if Synonym is of appropriate type, assuming stmt is valid
                return syn.getType() == EntityType::Stmt;
            },
            [](const std::string& str) { return str == "_"; }, // "_" is valid
            [](const auto&) { return false; } // Catch-all for unexpected types
    }, ref);
}

// ai-gen end