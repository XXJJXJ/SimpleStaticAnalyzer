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
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    WithPredicate(Ref ref1, Ref ref2);
    ~WithPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const WithPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<WithPredicate>> {
        std::size_t operator()(const shared_ptr<WithPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<WithPredicate>> {
        bool operator()(const shared_ptr<WithPredicate>& lhs, const shared_ptr<WithPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif  // WITHPREDICATE_H