#ifndef CALLSTPREDICATE_H
#define CALLSTPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


// Forward declaration of Strategy to avoid circular dependency
class Strategy;

class CallsTPredicate : public Predicate {
private:
    EntityRef lhs; // Left-hand side can be an int, Synonym, or "_"
    EntityRef rhs; // Right-hand side can be a Synonym or "_"
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    CallsTPredicate(EntityRef lhs, EntityRef rhs);
    ~CallsTPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const CallsTPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<CallsTPredicate>> {
        std::size_t operator()(const shared_ptr<CallsTPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<CallsTPredicate>> {
        bool operator()(const shared_ptr<CallsTPredicate>& lhs, const shared_ptr<CallsTPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif // CALLSTPREDICATE_H