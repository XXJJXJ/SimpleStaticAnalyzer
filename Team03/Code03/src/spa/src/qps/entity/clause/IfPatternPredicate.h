#ifndef SPA_IFPATTERNPREDICATE_H
#define SPA_IFPATTERNPREDICATE_H

#include "qps/entity/clause/Predicate.h"

class IfPatternPredicate : public Predicate {
private:
    Synonym ifSyn;
    EntityRef entRef;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager &qm) override;
public:
    IfPatternPredicate(Synonym ifSyn, EntityRef entRef);
    ~IfPatternPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const Predicate &other) const override;
    std::size_t hash() const override;
};

#endif //SPA_IFPATTERNPREDICATE_H
