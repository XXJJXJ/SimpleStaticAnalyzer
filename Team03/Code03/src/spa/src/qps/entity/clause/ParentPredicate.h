// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef PARENTPREDICATE_H
#define PARENTPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


class Strategy;

class ParentPredicate : public Predicate {
private:
    StatementRef lhs; // Parent statement reference
    StatementRef rhs; // Child statement reference
public:
    ParentPredicate(StatementRef lhs, StatementRef rhs);
    ~ParentPredicate() override = default;

    // Helper methods for validation
    static bool isValidStmtRef(const StatementRef& ref);

};

#endif // PARENTPREDICATE_H

// ai-gen end