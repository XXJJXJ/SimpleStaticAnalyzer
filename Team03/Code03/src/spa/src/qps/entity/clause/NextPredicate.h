#ifndef SPA_NEXTPREDICATE_H
#define SPA_NEXTPREDICATE_H
#include "Predicate.h"


class NextPredicate : public Predicate {
private:
    StatementRef lhs;
    StatementRef rhs;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;

public:
    NextPredicate(StatementRef lhs, StatementRef rhs);
};


#endif //SPA_NEXTPREDICATE_H
