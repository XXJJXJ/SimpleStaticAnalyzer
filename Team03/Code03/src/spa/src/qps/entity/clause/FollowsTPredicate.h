// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0

#ifndef FOLLOWSTPREDICATE_H
#define FOLLOWSTPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"

// Forward declaration of Strategy to avoid circular dependency
class Strategy;

class FollowsTPredicate : public Predicate {
private:
    StatementRef lhs; // Left-hand statement reference
    StatementRef rhs; // Right-hand statement reference
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;

public:
    FollowsTPredicate(StatementRef lhs, StatementRef rhs);
    ~FollowsTPredicate() override = default;
};

#endif // FOLLOWSTPREDICATE_H

// ai-gen end