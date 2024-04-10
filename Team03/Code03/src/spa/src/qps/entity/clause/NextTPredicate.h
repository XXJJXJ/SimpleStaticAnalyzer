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
    ~NextTPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const NextTPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<NextTPredicate>> {
        std::size_t operator()(const shared_ptr<NextTPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<NextTPredicate>> {
        bool operator()(const shared_ptr<NextTPredicate>& lhs, const shared_ptr<NextTPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}


#endif //SPA_NEXTTPREDICATE_H
