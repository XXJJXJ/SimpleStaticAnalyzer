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
    bool operator==(const AffectsPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
    template<>
    struct hash<shared_ptr<AffectsPredicate>> {
        std::size_t operator()(const shared_ptr<AffectsPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<AffectsPredicate>> {
        bool operator()(const shared_ptr<AffectsPredicate>& lhs, const shared_ptr<AffectsPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}


#endif //SPA_AFFECTSPREDICATE_H