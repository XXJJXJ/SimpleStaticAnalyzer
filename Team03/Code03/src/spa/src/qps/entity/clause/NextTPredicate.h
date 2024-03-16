#ifndef SPA_NEXTTPREDICATE_H
#define SPA_NEXTTPREDICATE_H
#include "Predicate.h"


class NextTPredicate : public Predicate {
private:
    StatementRef lhs;
    StatementRef rhs;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;

public:
    NextTPredicate(StatementRef lhs, StatementRef rhs);
    std::string toString() const override;
};


#endif //SPA_NEXTTPREDICATE_H
