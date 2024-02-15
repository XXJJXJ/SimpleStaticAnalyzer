#ifndef RELATIONSHIPPREDICATE_H
#define RELATIONSHIPPREDICATE_H

#include <string>
#include "qps/entity/strategy/Strategy.h"


class RelationshipPredicate {
public:
    virtual ~RelationshipPredicate() = default; // Ensure proper polymorphic deletion
    virtual shared_ptr<Strategy> getStrategy() const = 0; // Pure virtual function
};

#endif // RELATIONSHIPPREDICATE_H
