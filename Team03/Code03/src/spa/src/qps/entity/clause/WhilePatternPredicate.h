#ifndef SPA_WHILEPATTERNPREDICATE_H
#define SPA_WHILEPATTERNPREDICATE_H

#include "qps/entity/clause/Predicate.h"

class WhilePatternPredicate : public Predicate {
private:
    Synonym whileSyn;
    EntityRef entRef;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager &qm) override;
public:
    WhilePatternPredicate(Synonym whileSyn, EntityRef entRef);
    ~WhilePatternPredicate() override = default;
    PredicateType getType() const override;
    std::size_t hash() const override;
    bool operator==(const Predicate &other) const override;
};

#endif //SPA_WHILEPATTERNPREDICATE_H
