#ifndef WITHPREDICATE_H
#define WITHPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "qps/entity/clause/attribute/Ref.h"
#include "qps/entity/evaluation/HeaderTable.h"

// Forward declaration of Strategy to avoid circular dependency
class Strategy;

class WithPredicate : public Predicate {
private:
    Ref ref1;
    Ref ref2;
    shared_ptr<RowFilter> getRowFilter();
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager &qm) override;
public:
    WithPredicate(Ref ref1, Ref ref2);
    ~WithPredicate() override = default;
    PredicateType getType() const override;
    std::size_t hash() const override;
    bool operator==(const Predicate &other) const override;
};

#endif  // WITHPREDICATE_H