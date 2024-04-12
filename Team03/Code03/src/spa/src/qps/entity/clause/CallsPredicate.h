#ifndef CALLSPREDICATE_H
#define CALLSPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


// Forward declaration of Strategy to avoid circular dependency
class Strategy;

class CallsPredicate : public Predicate {
private:
    EntityRef lhs; // Left-hand side can be an int, Synonym, or "_"
    EntityRef rhs; // Right-hand side can be a Synonym or "_"
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    CallsPredicate(EntityRef lhs, EntityRef rhs);
    ~CallsPredicate() override = default;
    PredicateType getType() const override;
    std::size_t hash() const override;
    bool operator==(const Predicate &other) const override;
};

#endif // CALLSPREDICATE_H