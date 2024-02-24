// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef PARENTTPREDICATE_H
#define PARENTTPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


class Strategy;

class ParentTPredicate : public Predicate {
private:
    StatementRef lhs; // Ancestor statement reference
    StatementRef rhs; // Descendant statement reference
public:
    ParentTPredicate(StatementRef lhs, StatementRef rhs);
    ~ParentTPredicate() override = default;

    // Helper methods for validation
    static bool isValidStmtRef(const StatementRef& ref);

};

#endif // PARENTTPREDICATE_H

// ai-gen end