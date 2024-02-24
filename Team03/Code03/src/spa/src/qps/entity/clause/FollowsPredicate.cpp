// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#include "FollowsPredicate.h"
#include "common/spa_exception/SyntaxErrorException.h"


FollowsPredicate::FollowsPredicate(StatementRef lhs, StatementRef rhs) {
    if (!isValidStatementRef(lhs) || !isValidStatementRef(rhs) || isWildcard(rhs)) {
        throw SyntaxErrorException("Invalid argument for FollowsPredicate constructor");
    }

    this->lhs = std::move(lhs);
    this->rhs = std::move(rhs);

    if (std::holds_alternative<Synonym>(this->lhs)) {
        auto synonym = std::get<Synonym>(lhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
    if (std::holds_alternative<Synonym>(this->rhs)) {
        auto synonym = std::get<Synonym>(rhs);
        this->synonyms.push_back(std::make_shared<Synonym>(synonym));
    }
}


shared_ptr<HeaderTable> FollowsPredicate::getTable(QueryManager &qm) {
    auto table = qm.getFollowS();
}

// ai-gen end