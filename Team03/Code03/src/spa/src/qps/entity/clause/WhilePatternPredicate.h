#ifndef SPA_WHILEPATTERNPREDICATE_H
#define SPA_WHILEPATTERNPREDICATE_H

#include "qps/entity/clause/Predicate.h"

class WhilePatternPredicate : public Predicate {
private:
    Synonym whileSyn;
    EntityRef entRef;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    WhilePatternPredicate(Synonym whileSyn, EntityRef entRef);
    ~WhilePatternPredicate() override = default;
};


#endif //SPA_WHILEPATTERNPREDICATE_H
