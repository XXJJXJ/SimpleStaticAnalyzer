#ifndef SPA_AFFECTSPREDICATE_H
#define SPA_AFFECTSPREDICATE_H
#include "Predicate.h"


class AffectsPredicate : public Predicate {
private:
    StatementRef lhs;
    StatementRef rhs;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;

public:
    AffectsPredicate(StatementRef lhs, StatementRef rhs);
    [[nodiscard]] PredicateType getType() const override;
};


#endif //SPA_AFFECTSPREDICATE_H