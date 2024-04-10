#ifndef SPA_IFPATTERNPREDICATE_H
#define SPA_IFPATTERNPREDICATE_H

#include "qps/entity/clause/Predicate.h"


class IfPatternPredicate : public Predicate {
private:
    Synonym ifSyn;
    EntityRef entRef;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    IfPatternPredicate(Synonym ifSyn, EntityRef entRef);
    ~IfPatternPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const IfPatternPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<IfPatternPredicate>> {
        std::size_t operator()(const shared_ptr<IfPatternPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<IfPatternPredicate>> {
        bool operator()(const shared_ptr<IfPatternPredicate>& lhs, const shared_ptr<IfPatternPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}


#endif //SPA_IFPATTERNPREDICATE_H
