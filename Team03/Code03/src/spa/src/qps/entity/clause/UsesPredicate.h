// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0

#ifndef USESPREDICATE_H
#define USESPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


class Strategy;

using UsesLhsRef = std::variant<int, Synonym, std::string>; // Combination of procedure and statements ref

class UsesPredicate : public Predicate {
private:
    UsesLhsRef lhs; // Directly holds int, Synonym, or std::string
    EntityRef rhs; // Can be a synonym of type variable, a variable name, or "_"
public:
    UsesPredicate(UsesLhsRef lhs, EntityRef rhs);
    ~UsesPredicate() override = default;

    static bool isValidLhs(const UsesLhsRef& lhs);
    static bool isValidRhs(const EntityRef& rhs);
};

#endif // USESPREDICATE_H


// ai-gen end