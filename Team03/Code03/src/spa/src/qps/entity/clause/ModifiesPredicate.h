#ifndef MODIFIESPREDICATE_H
#define MODIFIESPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>

class Strategy;

// StatementRef: int, Synonym, or "_"
using StatementRef = std::variant<int, Synonym, std::string>;

// EntityRef: Synonym or string (for procedure names or variable names)
using EntityRef = std::variant<Synonym, std::string>;

// ModifiesLhsRef: Can be either StatementRef or EntityRef
using ModifiesLhsRef = std::variant<StatementRef, EntityRef>;

class ModifiesPredicate : public Predicate {
private:
    ModifiesLhsRef lhs; // Either a StatementRef or an EntityRef
    EntityRef rhs; // Can be a synonym of type variable, a variable name, or "_"
public:
    ModifiesPredicate(ModifiesLhsRef lhs, EntityRef rhs);
    ~ModifiesPredicate() override = default;

    std::shared_ptr<Strategy> getStrategy() const override;

    // Helper methods for validation
    static bool isValidLhs(const ModifiesLhsRef& lhs);
    static bool isValidRhs(const EntityRef& rhs);
};

#endif // MODIFIESPREDICATE_H

