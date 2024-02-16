// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef MODIFIESPREDICATE_H
#define MODIFIESPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>

class Strategy;

using ModifiesLhsRef = std::variant<int, Synonym, std::string>; // Combination of procedure and statements ref
using EntityRef = std::variant<Synonym, std::string>;

class ModifiesPredicate : public Predicate {
private:
    ModifiesLhsRef lhs; // Directly holds int, Synonym, or std::string
    EntityRef rhs; // Can be a synonym of type variable, a variable name, or "_"
public:
    ModifiesPredicate(ModifiesLhsRef lhs, EntityRef rhs);
    ~ModifiesPredicate() override = default;

    std::shared_ptr<Strategy> getStrategy() const override;

    static bool isValidLhs(const ModifiesLhsRef& lhs);
    static bool isValidRhs(const EntityRef& rhs);
};

#endif // MODIFIESPREDICATE_H


// ai-gen end