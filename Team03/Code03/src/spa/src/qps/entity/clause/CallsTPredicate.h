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
    std::size_t hash() const override;
    bool operator==(const Predicate &other) const override;
};

#endif // CALLSTPREDICATE_H