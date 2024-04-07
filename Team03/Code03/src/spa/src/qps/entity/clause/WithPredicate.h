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
public:
    WithPredicate(Ref ref1, Ref ref2);
    ~WithPredicate() override = default;
};

#endif  // WITHPREDICATE_H