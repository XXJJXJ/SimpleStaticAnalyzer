// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef PARENTPREDICATE_H
#define PARENTPREDICATE_H

#include "Predicate.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "PredicateUtils.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include <memory>

class ParentPredicate : public Predicate {
private:
    StatementRef lhs;
    StatementRef rhs;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;

public:
    ParentPredicate(StatementRef lhs, StatementRef rhs);
    ~ParentPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const ParentPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<ParentPredicate>> {
        std::size_t operator()(const shared_ptr<ParentPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<ParentPredicate>> {
        bool operator()(const shared_ptr<ParentPredicate>& lhs, const shared_ptr<ParentPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif // PARENTPREDICATE_H


// ai-gen end