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
    PredicateType getType() const override;
    bool operator==(const FollowsTPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<FollowsTPredicate>> {
        std::size_t operator()(const shared_ptr<FollowsTPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<FollowsTPredicate>> {
        bool operator()(const shared_ptr<FollowsTPredicate>& lhs, const shared_ptr<FollowsTPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif // FOLLOWSTPREDICATE_H

// ai-gen end