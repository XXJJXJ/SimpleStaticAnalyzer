// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0

#ifndef FOLLOWSPREDICATE_H
#define FOLLOWSPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


// Forward declaration of Strategy to avoid circular dependency
class Strategy;

class FollowsPredicate : public Predicate {
private:
    StatementRef lhs; // Left-hand side can be an int, Synonym, or "_"
    StatementRef rhs; // Right-hand side can be a Synonym or "_"
    bool isValidRow(const std::vector<std::shared_ptr<Entity>>& row) const;
public:
    FollowsPredicate(StatementRef lhs, StatementRef rhs);
    ~FollowsPredicate() override = default;
    [[nodiscard]] shared_ptr<BaseTable> getTable(QueryManager& qm) override;
};

#endif // FOLLOWSPREDICATE_H

// ai-gen end