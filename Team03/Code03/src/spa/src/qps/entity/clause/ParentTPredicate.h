// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef PARENTTPREDICATE_H
#define PARENTTPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "common/spa_exception/QPSEvaluationException.h"


class Strategy;

class ParentTPredicate : public Predicate {
private:
    StatementRef lhs; // Ancestor statement reference
    StatementRef rhs; // Descendant statement reference
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    ParentTPredicate(StatementRef lhs, StatementRef rhs);
    ~ParentTPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const ParentTPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<ParentTPredicate>> {
        std::size_t operator()(const shared_ptr<ParentTPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<ParentTPredicate>> {
        bool operator()(const shared_ptr<ParentTPredicate>& lhs, const shared_ptr<ParentTPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif // PARENTTPREDICATE_H

// ai-gen end