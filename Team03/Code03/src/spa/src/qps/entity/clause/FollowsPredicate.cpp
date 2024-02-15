// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsPredicate.h"

FollowsPredicate::FollowsPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs) || isWildcard(rhs)) {
        throw std::invalid_argument("Invalid argument for FollowsPredicate constructor");
    }
    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);
}

std::shared_ptr<Strategy> FollowsPredicate::getStrategy() const {
    // Implementation logic for returning the appropriate strategy
    return nullptr; // Placeholder return
}

// Checks the validity of input
bool FollowsPredicate::isValidStatementRef(const StatementRef& ref) {
    if (std::holds_alternative<Synonym>(ref)) {
        auto synonym = std::get<Synonym>(ref);
        return synonym.getType() == EntityType::Stmt;
    } else if (std::holds_alternative<std::string>(ref)) {
        return std::get<std::string>(ref) == "_";
    } else if (std::holds_alternative<int>(ref)) {
        // Assuming int is always a valid statement reference
        return true;
    }
    return false;
}

// Implement the isWildcard function to check if RHS is a wildcard
bool FollowsPredicate::isWildcard(const StatementRef& ref) {
    return std::holds_alternative<std::string>(ref) && std::get<std::string>(ref) != "_";
}
// You can implement additional methods here as needed, for example, methods to
// help determine if the lhs or rhs is an integer, synonym, or wildcard.

// ai-gen end