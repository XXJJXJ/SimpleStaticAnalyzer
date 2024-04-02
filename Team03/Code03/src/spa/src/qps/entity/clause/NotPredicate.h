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
};


#endif //SPA_NOTPREDICATE_H
