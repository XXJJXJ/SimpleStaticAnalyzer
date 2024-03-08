// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef MODIFIESPREDICATE_H
#define MODIFIESPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


class Strategy;

class ModifiesPredicate : public Predicate {
private:
    ProcAndStmtRef lhs; // Directly holds int, Synonym, or std::string
    EntityRef rhs; // Can be a synonym of type variable, a variable name, or "_"
  public:
    ModifiesPredicate(ProcAndStmtRef lhs, EntityRef rhs);
    ~ModifiesPredicate() override = default;
    [[nodiscard]] shared_ptr<BaseTable> getTable(QueryManager& qm) override;

    static bool isValidLhs(const ProcAndStmtRef& lhs);
    static bool isValidRhs(const EntityRef& rhs);
};

#endif // MODIFIESPREDICATE_H


// ai-gen end