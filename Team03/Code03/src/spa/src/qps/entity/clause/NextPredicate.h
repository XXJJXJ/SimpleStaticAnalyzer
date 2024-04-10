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
    ~NextPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const NextPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<NextPredicate>> {
        std::size_t operator()(const shared_ptr<NextPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<NextPredicate>> {
        bool operator()(const shared_ptr<NextPredicate>& lhs, const shared_ptr<NextPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif //SPA_NEXTPREDICATE_H
