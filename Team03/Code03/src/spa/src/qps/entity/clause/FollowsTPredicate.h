// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef FOLLOWSTPREDICATE_H
#define FOLLOWSTPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>

class Strategy;

class FollowsTPredicate : public Predicate {
private:
    StatementRef lhs; // Left-hand statement reference
    StatementRef rhs; // Right-hand statement reference
public:
    FollowsTPredicate(StatementRef lhs, StatementRef rhs);
    ~FollowsTPredicate() override = default;

    std::shared_ptr<Strategy> getStrategy() const override;

    // Helper methods for validation
    static bool isValidStmtRef(const StatementRef& ref);
};

#endif // FOLLOWSTPREDICATE_H

// ai-gen end