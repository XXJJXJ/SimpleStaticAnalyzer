#ifndef SPA_NOTPREDICATE_H
#define SPA_NOTPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/evaluation/BaseTable.h"
#include "qps/entity/evaluation/HeaderTable.h"

class NotPredicate : public Predicate {
private:
    shared_ptr<Predicate> predicate;
public:
    explicit NotPredicate(shared_ptr<Predicate> predicate);
    std::shared_ptr<BaseTable> getResultTable(QueryEvaluationContext &qec) override;
    PredicateType getType() const override;
    bool operator==(const NotPredicate &other) const;
    bool equals(const Predicate &other) const override;
    std::size_t hash() const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<NotPredicate>> {
        std::size_t operator()(const shared_ptr<NotPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<NotPredicate>> {
        bool operator()(const shared_ptr<NotPredicate>& lhs, const shared_ptr<NotPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif //SPA_NOTPREDICATE_H
