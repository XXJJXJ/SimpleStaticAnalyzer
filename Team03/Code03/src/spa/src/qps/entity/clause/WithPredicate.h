#ifndef WITHPREDICATE_H
#define WITHPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"
#include "qps/entity/evaluation/HeaderTable.h"

// Forward declaration of Strategy to avoid circular dependency
class Strategy;

class WithPredicate : public Predicate {
private:
    std::string ref1;
    std::string ref2;
public:
    WithPredicate(std::string ref1, std::string ref2);
 ~WithPredicate() override = default;
};

#endif  // WITHPREDICATE_H