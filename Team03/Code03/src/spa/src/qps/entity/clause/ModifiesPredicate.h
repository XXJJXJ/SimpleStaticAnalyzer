// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0

#ifndef MODIFIESPREDICATE_H
#define MODIFIESPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>

// Forward declaration of Strategy to avoid circular dependency
class Strategy;

// Define StatementRef to handle statement line number, synonym, or wildcard
using StatementRef = std::variant<int, Synonym, std::string>;

class ModifiesPredicate : public Predicate {
private:
    StatementRef lhs; // Left-hand side can be an int, Synonym, or "_"
    StatementRef rhs; // Right-hand side can be an Synonym or "_"
    // Private helper function declaration
    bool isValidStatementRef(const StatementRef& ref);
    bool isWildcard(const StatementRef& ref);
public:
    ModifiesPredicate(StatementRef lhs, StatementRef rhs);
    ~ModifiesPredicate() override = default;

    std::shared_ptr<Strategy> getStrategy() const override;

    // Additional methods for internal logic as needed
};

#endif // MODIFIESPREDICATE_H

// ai-gen end