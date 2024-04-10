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
    PredicateType getType() const override;
    bool operator==(const WhilePatternPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<WhilePatternPredicate>> {
        std::size_t operator()(const shared_ptr<WhilePatternPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<WhilePatternPredicate>> {
        bool operator()(const shared_ptr<WhilePatternPredicate>& lhs, const shared_ptr<WhilePatternPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif //SPA_WHILEPATTERNPREDICATE_H
