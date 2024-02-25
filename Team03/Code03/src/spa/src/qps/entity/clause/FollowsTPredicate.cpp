// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsTPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

FollowsTPredicate::FollowsTPredicate(StatementRef lhs, StatementRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidStmtRef(this->lhs) || !isValidStmtRef(this->rhs)) {
        throw SyntaxErrorException("Invalid arguments for FollowsTPredicate constructor");
    }
    if (std::holds_alternative<Synonym>(this->lhs)) {
        auto synonym = std::get<Synonym>(this->lhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
    if (std::holds_alternative<Synonym>(this->rhs)) {
        auto synonym = std::get<Synonym>(this->rhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
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