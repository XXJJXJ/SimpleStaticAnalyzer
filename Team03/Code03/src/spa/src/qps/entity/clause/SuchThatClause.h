#ifndef SUCHTHATCLAUSE_H
#define SUCHTHATCLAUSE_H

#include "Clause.h"
#include "RelationshipPredicate.h"
#include "qps/entity/strategy/Strategy.h"
#include <vector>
#include <memory>

class SuchThatClause : public Clause {
private:
    std::vector<std::shared_ptr<RelationshipPredicate>> predicates;

public:
    SuchThatClause() = default;
    void addPredicate(std::unique_ptr<RelationshipPredicate> predicate);
    std::vector<std::shared_ptr<Strategy>> getStrategies() const override;
};

#endif // SUCHTHATCLAUSE_H
