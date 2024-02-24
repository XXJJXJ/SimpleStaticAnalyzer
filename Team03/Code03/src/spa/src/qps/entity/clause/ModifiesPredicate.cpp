// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "ModifiesPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"

ModifiesPredicate::ModifiesPredicate(ModifiesLhsRef lhs, EntityRef rhs)
        : lhs(std::move(lhs)), rhs(std::move(rhs)) {
    if (!isValidLhs(this->lhs) || !isValidRhs(this->rhs)) {
        throw SyntaxErrorException("Invalid arguments for ModifiesPredicate constructor");
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