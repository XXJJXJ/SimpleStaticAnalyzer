// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/4018fd98-2d4f-488f-a857-7769d6a30be0
#ifndef MODIFIESPREDICATE_H
#define MODIFIESPREDICATE_H

#include "Predicate.h"
#include <memory>
#include <variant>
#include "PredicateUtils.h"


class Strategy;

class ModifiesPredicate : public Predicate {
private:
    ProcAndStmtRef lhs; // Directly holds int, Synonym, or std::string
    EntityRef rhs; // Can be a synonym of type variable, a variable name, or "_"
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override;
public:
    ModifiesPredicate(ProcAndStmtRef lhs, EntityRef rhs);
    ~ModifiesPredicate() override = default;
    PredicateType getType() const override;
    bool operator==(const ModifiesPredicate &other) const;
    std::size_t hash() const override;
    bool equals(const Predicate &other) const override;
};

namespace std {
	template<>
    struct hash<shared_ptr<ModifiesPredicate>> {
        std::size_t operator()(const shared_ptr<ModifiesPredicate>& pred) const {
            return pred->hash();
        }
    };
    template <>
    struct equal_to<shared_ptr<ModifiesPredicate>> {
        bool operator()(const shared_ptr<ModifiesPredicate>& lhs, const shared_ptr<ModifiesPredicate>& rhs) const {
            return *lhs == *rhs;
        }
    };
}

#endif // MODIFIESPREDICATE_H


// ai-gen end