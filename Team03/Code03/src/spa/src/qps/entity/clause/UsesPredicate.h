// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0

#ifndef USESPREDICATE_H
#define USESPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


class Strategy;


class UsesPredicate : public Predicate {
private:
    ProcAndStmtRef lhs; // Directly holds int, Synonym, or std::string
    EntityRef rhs; // Can be a synonym of type variable, a variable name, or "_"
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    UsesPredicate(ProcAndStmtRef lhs, EntityRef rhs);
    ~UsesPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const UsesPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<UsesPredicate>> {
        std::size_t operator()(const shared_ptr<UsesPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<UsesPredicate>> {
        bool operator()(const shared_ptr<UsesPredicate>& lhs, const shared_ptr<UsesPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}
#endif // USESPREDICATE_H


// ai-gen end