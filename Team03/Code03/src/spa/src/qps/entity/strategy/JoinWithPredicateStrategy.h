#ifndef JOIN_WITH_PREDICATE_STRATEGY_H
#define JOIN_WITH_PREDICATE_STRATEGY_H

#include "Strategy.h"
#include "qps/entity/clause/Predicate.h"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include <memory>

class JoinWithPredicateStrategy : public Strategy {
private:
    std::shared_ptr<Predicate> predicate;

public:
    explicit JoinWithPredicateStrategy(std::shared_ptr<Predicate> pred);
    void execute(QueryEvaluationContext &context) override;
    std::string toString() const;
};

#endif // JOIN_WITH_PREDICATE_STRATEGY_H
